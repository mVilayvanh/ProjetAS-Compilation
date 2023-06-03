#include "ParseAsm.h"
#include <stdarg.h>

int labelcount = 0;
int hasElse = 0;
int npush = 0;
char buffer[BUFFERSIZE] = "";
char *funcName = NULL;

static void write_if(FILE * f , Node *node,SymbolTable * global , SymbolTable * local);
static void write_function_call(FILE *f, Node *node, SymbolTable *global, SymbolTable *local);
static void translate_body(FILE *f, Node *node, SymbolTable *global, SymbolTable *local);
static void write_bool_token(FILE *f, Node *node, SymbolTable *global, SymbolTable *local ,int tway , int fway);
static void translate_Expr_To_Asm(FILE * f, Node *node, SymbolTable *global, SymbolTable *local);

/**
 * Writes a string to the output buffer.
 * If the size of the buffer exceeds the maximum size (BUFFERSIZE),
 * its content is written to the output file (f) and the buffer is reset.
 *
 * @param f The output file to write the buffer to.
 * @param suffix The string to append to the buffer.
 * @param ... Additional arguments to be formatted into the string (if used).
 */
static void write_on_buffer(FILE *f, char *suffix, ...){
    char tmp[BUFFERSIZE] = "";
    va_list list;
    if (strlen(buffer) + strlen(suffix) >= BUFFERSIZE) {
        fprintf(f, "%s", buffer);
        // reset buffer
        buffer[0] = '\0';
    }
    va_start(list, suffix);
    vsprintf(tmp, suffix, list);
    va_end(list);
    strcat(buffer, tmp);
}

static void get_var_addr(FILE *f, Node *node, SymbolTable *global, SymbolTable *local){
    Symbol *sym;
    Sym_scope scope;
    if (node->label == Ident){
        sym = search_symbol(global, local, node->name, NULL, &scope);
        if (scope == LOCAL){
            write_on_buffer(f, "\tmov rax, qword [rbp - %d]\n", sym->reladdr);
        } else if (scope == GLOBAL){
            if (sym->table){
                write_function_call(f, node, global, local);
            } else {
                write_on_buffer(f, "\tmov eax, dword [globals + %d]\n", sym->reladdr);
            }
        }
    } else if (node->label == Num){
        write_on_buffer(f, "\tmov rax, %d\n", node->val);
    } else if (node->label == UnaryAddsub){
        write_on_buffer(f, "\tmov rax, ");
        write_on_buffer(f, "%s", node->name);
        write_on_buffer(f, "%d\n", FIRSTCHILD(node)->val);
    } else if (node->label == Character){
        write_on_buffer(f, "\tmov rax, %s\n", node->name);
    } else if (isOperand(node)){
        translate_Expr_To_Asm(f, node, global, local);
        write_on_buffer(f, "\tpop rax\n");
        npush--;
    }
}

/**
 * Moves to the declaration of global variables and generates assembly code for them.
 * 
 * @param node The current node being processed.
 * @param f The file to write the assembly code to.
 */
static void write_global_var_area(FILE *f, SymbolTable *global){
    // If no param (number of global variable is 0), .bss section is not requiered
    if (global->nparam == 0){
        return;
    }
    write_on_buffer(f, "section .bss\n");
    write_on_buffer(f, "globals: resd %d\n", global->nparam);
}

/**
 * Writes the initialization code at the beginning of the assembly file.
 * 
 * @param f The file to write the assembly code to.
 * @param node The root node of the AST.
 */
static void write_init(FILE * f, SymbolTable * global){
    if (f == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }
    write_global_var_area(f, global);
    write_on_buffer(f, "section .text\n");
    for (int i = 0; i < global->size; i++){
        if(global->symbols[i].table != NULL){
            if (strcmp("main", global->symbols[i].name) == 0){
                write_on_buffer(f, "global _start\n");
            } else {
                write_on_buffer(f, "global %s\n", global->symbols[i].name);
            }
        }
    }
}

/**
 * Writes the end code to the assembly file.
 * 
 * @param f The file to write the assembly code to.
 */
static void write_return(FILE * f, Node *node, SymbolTable *global, SymbolTable *local){
    if (node){
        get_var_addr(f, node, global, local);
    }
    if (strcmp(funcName, "main") == 0){
        write_on_buffer(f, "\tmov rdi, rax\n\tmov rax, 60\n\tsyscall\n");
    } else {
        write_on_buffer(f, "\tmov rsp, rbp\n\tpop rbp\n\tret\n");
    }
}

/**
 * Writes assembly code for a leaf node.
 * 
 * @param f The file to write the assembly code to.
 * @param leaf The leaf node.
 */
static void write_leaf(FILE *f, Node *leaf, SymbolTable *global, SymbolTable *local){
    Symbol *sym;
    Sym_scope scope;
    switch(leaf->label) {
        case Num:
            write_on_buffer(f, "\t; Add Leaf\n\tmov eax, %d\n\tpush rax\n", leaf->val);
            break;
        case Character:
            // Since Characters are only of size 1 + \0, retriving respectif ascii value
            write_on_buffer(f, "\t; Add Leaf\n\tmov eax, %d\n\tpush rax\n", leaf->name[1] - 0);
            break;
        case Ident:
            sym = search_symbol(global, local, leaf->name, NULL, &scope);
            if (scope == LOCAL){
                write_on_buffer(f, "\tmov rax, qword [rbp - %d]\n", sym->reladdr);
                write_on_buffer(f, "\tpush rax\n");
            } else if (scope == GLOBAL){
                // If has a sym table, it means it is a function
                if (sym->table){
                    write_function_call(f, leaf, global, local);
                    write_on_buffer(f, "\tpush rax\n");
                } else {
                    write_on_buffer(f, "\tmov eax, dword [globals + %d]\n", sym->reladdr);
                    write_on_buffer(f, "\tpush rax\n");
                }
            }
            break;
        default:
            break;
    } 
    npush++;
}

/**
 * Writes assembly code for addition or subtraction operation.
 * 
 * @param f The file to write the assembly code to.
 * @param node The node representing the addition or subtraction operation.
 */
static void write_addsub(FILE * f, Node *node){
    if (strcmp("+", node->name) == 0){
        write_on_buffer(f, 
        "\t; Compute add\n\tpop rcx\n\tpop rax\n\tadd rax, rcx\n\tpush rax\n");
    } 
    else {
        write_on_buffer(f,
            "\t; Compute sub\n\tpop rcx\n\tpop rax\n\tsub rax, rcx\n\tpush rax\n");
    }
    npush--;
}

/**
 * Writes assembly code for addition or subtraction operation.
 * 
 * @param f The file to write the assembly code to.
 * @param node The node representing the addition or subtraction operation.
 */
static void write_divstar(FILE * f, Node *node){
    if (strcmp(node->name, "*") == 0) {
        write_on_buffer(f,
                "\t; Compute Mul\n\tpop rcx\n\tpop rax\n\timul rax, rcx\n\tpush rax\n");
    } else {
         write_on_buffer(f,
                "\t; Compute Div\n\tpop rcx\n\tpop rax\n\tidiv rcx\n\tpush rax\n");
    }
    npush--;
}

static void write_parameter(FILE *f, Node *node, SymbolTable *global, SymbolTable *local, int paramno){
    get_var_addr(f, node, global, local);
    switch (paramno){
    case 1:
        write_on_buffer(f, "\tmov rdi, rax\n");
        break;
    case 2:
        write_on_buffer(f, "\tmov rsi, rax\n");
        break;
    case 3:
        write_on_buffer(f, "\tmov rdx, rax\n");
        break;
    case 4:
        write_on_buffer(f, "\tmov rcx, rax\n");
        break;
    case 5:
        write_on_buffer(f, "\tmov r8, rax\n");
        break;
    case 6:
        write_on_buffer(f, "\tmov r9, rax\n");
        break;
    default:
        write_on_buffer(f, "\tpush rax\n");
        npush++;
        break;
    }
}

static void write_function_call(FILE *f, Node *node, SymbolTable *global, SymbolTable *local){
    int paramno = 0, i = 0;
    Node *parameter = FIRSTCHILD(FIRSTCHILD(node));
    // According to C standard, no more than 127 arguments can be given
    Node *todo[128];
    // Has at least one non void parameter
    if (parameter->label != Type){
        paramno = 1;
        for (; parameter != NULL; parameter = NEXTSIBLING(parameter)){
            if (paramno < 7){
                write_parameter(f, parameter, global, local, paramno);
                paramno++;
            } else {
                todo[i] = parameter;
                i++;
                paramno++;
            }
        }
        // If there is over 6 parameters, push them
        if (paramno > 6){
            for (i = i - 1; i >= 0; i--){
                write_parameter(f, todo[i], global, local, paramno);
            }
        }
    }
    // Case alignement is required
    if (npush % 2 != 0){
        // Align stack
        write_on_buffer(f, "\tsub rsp, 8\n");
        write_on_buffer(f, "\tcall %s\n", node->name);
        // Restore stack
        write_on_buffer(f, "\tadd rsp, 8\n");
    } else {
        write_on_buffer(f, "\tcall %s\n", node->name);
    }
    // Restore stack in case parameters has been pushed
    while (paramno - 1 > 6){
        write_on_buffer(f, "\tpop rcx\n");
        paramno--;
        npush--;
    }
}

/**
 * Writes assembly code for order comparison operations (<, >, <=, >=).
 * 
 * @param f The file to write the assembly code to.
 * @param node The node representing the order comparison operation.
 */
static void write_order(FILE * f , Node * node, SymbolTable *global, SymbolTable *local,int tway , int fway){
    get_var_addr(f,FIRSTCHILD(node),global,local);
    write_on_buffer(f,"\tpush rax\n");
    get_var_addr(f,SECONDCHILD(node),global,local);
    write_on_buffer(f,"\tpush rax\n");
    write_on_buffer(f,"\tpop rcx\n\tpop rax\n");
    if (strcmp(node->name ,"<") == 0 ){
        write_on_buffer(f,"\tcmp rax, rcx\n\tjl .E%d\n",tway);
    }else if (strcmp(node->name ,">") == 0 ){
        write_on_buffer(f,"\tcmp rax, rcx\n\tjg .E%d\n",tway);
    }else if (strcmp(node->name ,"<=") == 0 ){
        write_on_buffer(f,"\tcmp rax, rcx\n\tjle .E%d\n",tway);
    }else if (strcmp(node->name ,">=") == 0 ){
        write_on_buffer(f,"\tcmp rax, rcx\n\tjge .E%d\n",tway);
    }
}

static void write_and(FILE * f , Node *node, SymbolTable * global , SymbolTable * local,int tway , int fway){
    int ttemp = labelcount++;
    write_bool_token(f,FIRSTCHILD(node),global,local,ttemp,fway);
    write_on_buffer(f,"\tjmp .E%d\n.E%d:\n",fway , ttemp);
    write_bool_token(f,SECONDCHILD(node),global,local,tway,fway);
}

static void write_or(FILE * f , Node *node, SymbolTable * global , SymbolTable * local, int tway , int fway){
    int ftemp = labelcount++;
    write_bool_token(f,FIRSTCHILD(node),global,local,tway ,ftemp);
    write_on_buffer(f,"\tjmp .E%d\n.E%d:\n",ftemp, ftemp);
    write_bool_token(f,SECONDCHILD(node),global,local,tway,fway);
}

/**
 * Writes assembly code for equality comparison operations (==, !=).
 * 
 * @param f The file to write the assembly code to.
 * @param node The node representing the equality comparison operation.
 */
static void write_eq(FILE * f , Node * node, SymbolTable *global, SymbolTable *local , int tway , int fway){
    get_var_addr(f,FIRSTCHILD(node),global,local);
    write_on_buffer(f,"\tpush rax\n");
    get_var_addr(f,SECONDCHILD(node),global,local);
    write_on_buffer(f,"\tpush rax\n");
    write_on_buffer(f,"\tpop rcx\n\tpop rax\n");
    if (strcmp(node->name ,"==") == 0 ){
        write_on_buffer(f,"\t; Compute Eq\n\tcmp rax, rcx\n\tje .E%d\n",tway);
    }else if (strcmp(node->name ,"!=") == 0 ){
        write_on_buffer(f,"\t; Compute Eq\n\tcmp rax, rcx\n\tjne .E%d\n",tway);
    }
}

/**
 * Writes assembly code for the expr statement.
 * 
 * @param f The file to write the assembly code to.
 * @param node The node representing the expr statement.
 */
static void write_expr(FILE *f, Node *node, SymbolTable *global, SymbolTable *local){
    switch (node->label){
        case Ident:
            write_leaf(f, node, global, local);
            break;
        case Num:
            write_leaf(f, node, global, local);
            break;
        case Character:
            write_leaf(f, node, global, local); 
            break;
        case Addsub:
            write_addsub(f, node);
            break;
        case Divstar:
            write_divstar(f, node);
            break;
        default:
            //fprintf(stderr, "Should not be here\n");
            break;
    }
}

static void write_bool_token(FILE *f, Node *node, SymbolTable *global, SymbolTable *local ,int tway , int fway){
    switch(node->label){
        case Order:
            write_order(f, node,global,local,tway,fway);
            break;
        case Eq:
            write_eq(f, node,global,local,tway, fway);
            break;
        case and:
            write_and(f, node,global,local,tway,fway);
            break;
        case or:
            write_or(f, node,global,local,tway,fway);
            break;
        default:
            get_var_addr(f, node, global, local);
            write_on_buffer(f, "\tcmp rax, 0\n");
            write_on_buffer(f, "\tjne .E%d\n", tway);
            break;
    }
}

static void write_if(FILE * f , Node *node,SymbolTable * global , SymbolTable * local){
    int tway = labelcount++;
    int fway = labelcount++;
    int temp = fway;
    write_bool_token(f,FIRSTCHILD(node),global,local,tway,fway);
    Node * node_else  = node->nextSibling;
    // Translation of if statement
    // Translation of else statement if exists
    if(node_else != NULL  && node_else->label == _else_){
        hasElse = 1;
        fway = labelcount++;
        write_on_buffer(f,"\tjmp .E%d\n",fway);
        write_on_buffer(f,".E%d:\n",tway);
        translate_body(f,SECONDCHILD(node),global,local);
        write_on_buffer(f,"\tjmp .E%d\n.E%d:\n", temp, fway);
        translate_body(f,FIRSTCHILD(node_else),global,local);
        write_on_buffer(f,".E%d:\n", temp);
    } else {
        write_on_buffer(f,"\tjmp .E%d\n",fway);
        write_on_buffer(f,".E%d:\n",tway);
        translate_body(f,SECONDCHILD(node),global,local);
        write_on_buffer(f,".E%d:\n", fway);
    }
}

static void write_while(FILE * f , Node *node,SymbolTable * global , SymbolTable * local){
    int condway = labelcount++, tway = labelcount++, fway = labelcount++;
    write_on_buffer(f, "\tjmp .E%d\n.E%d:\n", condway, tway);
    translate_body(f, SECONDCHILD(node), global, local);
    write_on_buffer(f, ".E%d:\n", condway);
    write_bool_token(f, FIRSTCHILD(node), global, local, tway, fway);
    write_on_buffer(f, ".E%d:\n", fway);
}

/**
 * Checks if both children of a node are either "Num" nodes or "Character" nodes.
 * 
 * @param node The node to check.
 * @return 1 if both children are "Num" nodes or "Character" nodes, 0 otherwise.
 */
static int both_child_are_leaf(Node *node){
    return FIRSTCHILD(node) && !FIRSTCHILD(node)->firstChild
        && SECONDCHILD(node) && !SECONDCHILD(node)->firstChild;
}

/**
 * Translates an expression tree to assembly code.
 * 
 * @param f The file to write the assembly code to.
 * @param node The root node of the expression tree.
 */
static void translate_Expr_To_Asm(FILE * f, Node *node, SymbolTable *global, SymbolTable *local){
    // Left child = FIRST CHILD
    // Right child = NEXT SIBLING
    
    if (node){
        // Checks if both children are primitive nodes
        if (both_child_are_leaf(node)){
            write_expr(f, FIRSTCHILD(node), global, local);
            write_expr(f, SECONDCHILD(node), global, local);
            write_expr(f, node, global, local);
        } else {
            // Fix this case later
            if (node->label == Ident || node->label == Character || node->label == Num){
                write_expr(f, node, global, local);
                return;
            }
            
            // Recursively translate the left and right children
            translate_Expr_To_Asm(f, FIRSTCHILD(node), global, local);
            translate_Expr_To_Asm(f, SECONDCHILD(node), global, local);
            
            // Write the current node to the assembly code
            write_expr(f, node, global, local);
        }
    }
}

/**
 * Writes assembly code for an assignment operation.
 * 
 * @param f The file to write the assembly code to.
 * @param node The node representing the assignment operation.
 */
static void write_assign_in_suite_instr(FILE *f, Node *node, SymbolTable *global, SymbolTable *local){
    Sym_scope scope;
    Symbol *sym = NULL;
    get_var_addr(f, SECONDCHILD(node), global, local);
    sym = search_symbol(global, local, FIRSTCHILD(node)->name, NULL, &scope);
    if (scope == LOCAL)
        write_on_buffer(f, "\tmov qword [rbp - %d], rax\n", sym->reladdr);
    else
        write_on_buffer(f, "\tmov dword [globals + %d], eax\n", sym->reladdr);
}

static void write_var_loc_declaration(FILE *f, Node *node, SymbolTable *global, SymbolTable *local){
    Node *child, *subChild;
    Symbol *sym;
    Sym_scope scope;
    for (child = FIRSTCHILD(node); child != NULL; child = NEXTSIBLING(child)){
        for (subChild = FIRSTCHILD(child); subChild != NULL; subChild = NEXTSIBLING(subChild)){
            if (subChild->label == Ident){
                write_on_buffer(f, "\tpush rax\n");
                npush++;
            } else if (subChild->label == Assign){
                get_var_addr(f, SECONDCHILD(subChild), global, local);
                sym = search_symbol(global, local, FIRSTCHILD(subChild)->name, NULL, &scope);
                if (scope == GLOBAL){
                    write_on_buffer(f, "\tmov dword [globals + %d], eax\n", sym->reladdr);
                } else if (scope == LOCAL){
                    write_on_buffer(f, "\tpush rax\n");
                    npush++;
                }
            }
        }
    }
}

/**
 * Searches for operations in the tree and performs corresponding actions.
 * 
 * @param f The file to write the assembly code to.
 * @param node The starting node for the search.
 */
static void translate_body(FILE *f, Node *node, SymbolTable *global, SymbolTable *local){
    for (Node *child = FIRSTCHILD(node); child != NULL; child = child->nextSibling) {
        if (child->label == DeclarVarLoc){
            write_var_loc_declaration(f, child, global, local);
            continue;
        }
        if (child->label == _if_){
            write_if(f, child, global, local);
            if (hasElse){
                hasElse = 0;
                child = child->nextSibling;
                continue;
            } else {
                continue;
            }
        }
        if (child->label == Assign) {
            write_assign_in_suite_instr(f, child, global, local);
            continue;
        }
        if (node->label == SuiteInstr && child->label == Ident){
            // Must be function call
            write_function_call(f, child, global, local);
            continue;
        }
        if (child->label == _while_){
            write_while(f, child, global, local);
            continue;
        }
        if (child->label == _return_){
            // Write exit function
            write_return(f, FIRSTCHILD(child), global, local);
            continue;
        }
        translate_body(f, child, global, local);
    } 
}

static Node *move_to_body(const Node *node){
    // First child always exists when starting at DeclFonct
    if (node->label == DeclFonct)
        return SECONDCHILD(node);
    return NULL;
}

/**
 * Generates an assembly file based on the given symbol table and node.
 *
 * @param global A pointer to the global symbol table.
 * @param node A pointer to the root node of the syntax tree.
 */
void write_Asm(SymbolTable * global){
    Node *body = NULL;
    SymbolTable *local = NULL;
    // A retirer. Entrer dans write asm uniquement si aucune erreur sem
    FILE * f = fopen("ano.asm", "w");
    write_init(f, global);
    for (int i = 0; i < global->size; i++){
        if(global->symbols[i].table != NULL){
            local = (SymbolTable *)global->symbols[i].table;
            body = global->symbols[i].funcNode;
            funcName = global->symbols[i].name;
            move_to_body(body);
            if (strcmp("main", funcName) == 0){
                write_on_buffer(f, "_start:\n\tmov rbp, rsp\n");
            } else {
                write_on_buffer(f, "%s:\n", global->symbols[i].name);
            }
            
            if (body){
                translate_body(f, body, global, local);
            } 
            if (global->symbols[i].type == VOID_TYPE){
                write_on_buffer(f, "\tret\n");
            }
        }
    }
    fprintf(f, "%s", buffer);
    fclose(f);
}

