#include "symbole.h"

#include <stdarg.h>

int hasReturn = 0;
int voidOperand = 0;
Sym_scope instance = GLOBAL;

Symbol *search_symbol(SymbolTable *global, SymbolTable *local, char *name, int *index,
        Sym_scope *scope){
    int i;
    for (i = local->size - 1; i >= 0; i--){
        if (strcmp(local->symbols[i].name, name) == 0){
            if (index){
                *index = i;
            }
            if (scope){
                *scope = LOCAL;
            }
            return &(local->symbols[i]);
        }
    }
    for (i = global->size - 1; i >= 0; i--){
        if (strcmp(global->symbols[i].name, name) == 0){
            if (index){
                *index = i;
            }
            if (scope){
                *scope = GLOBAL;
            }
            return &(global->symbols[i]);
        }
    } 
    if (index){
        *index = -1;
    }
    if (scope){
        *scope = NOT_SYM;
    }
    return NULL;
}

int is_empty_table(const SymbolTable *table){
    if (!table){
        return 0;
    }
    return table->size == 0;
}

static void print_warn(Err_c  code , Node * node , ...){
    switch (code){
        case CHAR_EXPECTED:
            fprintf(stderr, WARN_CHAR_EXPECTED, node->lineno);
            break;
        default:
            break;
    }
}

static void raise_sem_err(Err_c code, Node *node) {
    // Print respective message depending on semantic error code
    err_flag = 1;
    switch (code) {
        case UNDECLARED:
            fprintf(stderr, ERR_UNDEC_VAR, node->lineno, node->name);
            break;
        case REDECLARED:
            fprintf(stderr, ERR_REDEC_VAR, node->lineno, node->name);
            break;
        case RET_WITH_NO_VALUE:
            fprintf(stderr, ERR_RET_VOID_MISMATCH, node->lineno);
            break;
        case FUNC_ARG_NUMBER:
            fprintf(stderr, ERR_FUNC_ARG_NUMBER, node->lineno, node->name);
            break;
        case FUNC_NAME_USED:
            fprintf(stderr, ERR_FUNC_NAME_USED, node->lineno, node->name);
            break;
        case FUNC_WRONG_USAGE:
            fprintf(stderr, ERR_FUNC_WRONG_USAGE, node->lineno, node->name);
            break;
        case RETURN_TOKEN_MISSING:
            fprintf(stderr, ERR_MISSING_RET_TOKEN, node->lineno);
            break;
        case NO_MAIN:
            fprintf(stderr, ERR_NO_MAIN);
            break;
        case MAIN_WRONG_TYPE:
            fprintf(stderr, ERR_MAIN_WRONG_TYPE);
            break;
        case VAR_AS_FUNC_CALL:
            fprintf(stderr, ERR_VAR_AS_FUNC_CALL, node->lineno, node->name);
            break;
        case RET_WITH_VALUE:
            fprintf(stderr, ERR_RET_VALUE_MISMATCH, node->lineno);
            break;
        case VOID_TYPE_ARGUMENT:
            fprintf(stderr, ERR_VOID_TYPE_AS_ARGUMENT, node->lineno);
            break;
        case VOID_TYPE_AS_OPERAND:
            fprintf(stderr, ERR_VOID_TYPE_AS_OPERAND, node->lineno, node->name);
            break;
        case VOID_TYPE_AS_RETVAL:
            fprintf(stderr, ERR_VOID_TYPE_AS_RETVAL, node->lineno, node->name);
            break;
        case VOID_TYPE_AS_ASSIGNEMENT:
            fprintf(stderr, ERR_VOID_TYPE_AS_ASSIGNEMENT, node->lineno, node->name);
        default:
            break;
    }
}

static void checking_operand_format(SymbolTable *global, SymbolTable *local, Node *node, int *retval){
    Node *cur;
    Symbol *sym;
    for (cur = FIRSTCHILD(node); cur != NULL; cur = cur->nextSibling){
        if (cur->label == Ident){
            sym = search_symbol(global, local, cur->name, NULL, NULL);
            if (!sym){
                raise_sem_err(UNDECLARED, cur);
                if (retval){
                    *retval = 1;
                }
            } else if (sym->type == VOID_TYPE){
                voidOperand = 1;
                raise_sem_err(VOID_TYPE_AS_OPERAND, cur);
                if (retval){
                    *retval = 1;
                }
            }
            checking_operand_format(global, local, cur, retval);
        }
    }
}

static int init_sym_table(SymbolTable **dest){
    int i;
    SymbolTable *res = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (!res){
        return 0;
    }
    // Set all attributes to default value
    res->capacity = INIT_CAPACITY;
    res->size = 0;
    res->symbols = (Symbol *)malloc(INIT_CAPACITY * sizeof(Symbol));
    if (!res->symbols){
        return 0;
    }
    // Initialize all pointer to NULL
    for (i = 0; i < INIT_CAPACITY; i++){
        res->symbols[i].table = NULL;
        res->symbols[i].funcNode = NULL;
    }
    res->nparam = 0;
    res->total_bytes = 0 ;
    *dest = res;
    return 1;
}

static void add_bytes(SymbolTable *table) {
    switch (instance) {
        case GLOBAL:
            table->total_bytes += 4;
            break;
        case LOCAL:
            table->total_bytes += 8;
            break;       
        default:
            break;
    }
}

static int add_symbol(SymbolTable *table, char *name, Types type, SymbolTable *ptr, Node *funcNode){
    // Vérifie si le symbole existe déjà dans la table
    for (int i = 0; i < table->size; i++){
        if (strcmp(table->symbols[i].name, name) == 0){
            return 0;
        }
    }
    // Le symbole n'existe pas encore, on l'ajoute
    // Augmente la capacité de x2 si nécessaire 
    if (table->size >= table->capacity){
        table->capacity *= 2;
        table->symbols = (Symbol *)realloc(table->symbols, table->capacity * sizeof(Symbol));
    }
    // Initialise les autres champs du symbole selon les besoins
    table->symbols[table->size].name = strdup(name);
    table->symbols[table->size].type = type; 
    // Case it is a function and there is a table linked to this symbol
    if (ptr){
        table->symbols[table->size].table = ptr;
        table-> symbols[table->size].funcNode = funcNode;
    } else {
        add_bytes(table);
    }
    table->size++;
    return 1;
}

static int select_type(char *name){
    if (strcmp(name, "int") == 0){
        return INT_TYPE;
    } else if (strcmp(name, "char") == 0){
        return CHAR_TYPE;
    } else if (strcmp(name, "void") == 0){
        return VOID_TYPE;
    } else {
        return UNDEFINED;
    }
}

int nb_param_of_function(SymbolTable *table, char *name){
    SymbolTable *temp = NULL;
    // Search among functions in global table 
    for(int i = 0 ; i < table->size ; i++){
        // If found in table, gets its number of parameter
        if(strcmp(table->symbols[i].name, name) == 0){
            temp = (SymbolTable *)(table->symbols[i].table);
            return temp->nparam;
        }
    }
    return 0;
}

static int count_argument(Node * node){
    int i = 0;
    Node *child;
    // le cas on le type de l'arg est void 

    if (FIRSTCHILD(node)->name != NULL){
        if(strcmp(FIRSTCHILD(node)->name, "void") == 0){
            return i;
        }
    }
    for (child = FIRSTCHILD(node); child != NULL; child = child->nextSibling){
        i++;
    }
    return i;
}

static int check_argument(SymbolTable *global, SymbolTable *local, SymbolTable *funcTable,
        Node *node, unsigned int nbParam){
    Node *child ,*arguments;
    Symbol *tmp;
    Types type = UNDEFINED;
    int i = 0, err = 0, retval = 0;
    // Compute type checking similarity between current function's node and parameters in function where
    // it is called
    if(FIRSTCHILD(node) == NULL){
        raise_sem_err(FUNC_WRONG_USAGE, node);
        return 1;
    }
    arguments = FIRSTCHILD(node);
    for (child = arguments->firstChild; child != NULL && i < nbParam; child = child->nextSibling, i++){
        if (child->label == Ident){
            tmp = search_symbol(global, local, child->name, NULL, NULL);
            // is function
            if (tmp && tmp->funcNode) {
                err = check_argument(global, local, tmp->table, child, nb_param_of_function(global, tmp->name));
                if (err){
                    retval = 1;
                }
            }
            // Not found
            if (!tmp){
                raise_sem_err(UNDECLARED, child);
                retval = 1;
            } else {
                type = tmp->type;
                // Void type variable is not allowed
                if (type == VOID_TYPE){
                    raise_sem_err(VOID_TYPE_ARGUMENT, child);
                    retval = 1;
                }
            }
        } else if (child->label == Num) {
            type = INT_TYPE;
        } else if (child->label == Character) {
            type = CHAR_TYPE;
        } else if (isOperand(child)){
            checking_operand_format(global, local, child, &err);
            if (err){
                raise_sem_err(VOID_TYPE_ARGUMENT, child);
            }
        }
        if (type != UNDEFINED && funcTable->symbols[i].type == CHAR_TYPE && type == INT_TYPE){
            print_warn(CHAR_EXPECTED, child);
        } 
    }
    if (count_argument(arguments) != nbParam){
        raise_sem_err(FUNC_ARG_NUMBER, node);
        retval = 1;
    }
    return retval;
}

static Types select_correct_type(SymbolTable *global, SymbolTable *local , Node *node){
    Types res = UNDEFINED;
    Symbol *tmp;
    int err = 0;
    switch (node->label){
    case Num:
        res = INT_TYPE;
        break;
    case Character:
        res = CHAR_TYPE;
        break;
    case Ident:
        tmp = search_symbol(global, local, node->name, NULL, NULL);
        if (tmp && tmp->funcNode == NULL && !FIRSTCHILD(node)){
            res = tmp->type;
        }
        else if (tmp && tmp->funcNode != NULL){
            check_argument(global, local, tmp->table, node, nb_param_of_function(global, node->name));
            res = tmp->type;
        } else {
            res = UNDEFINED;
        }
        break;
    default:
        // Is boolean or addsub/divstar statement
        checking_operand_format(global, local, node, &err);
        if (err){
            res = UNDEFINED;
        } else {
            res = INT_TYPE;
        }
        break;
    }
    return res;
}

static int add_variable(SymbolTable *global, SymbolTable *local, Node *node){
    Node *child = NULL;
    Node *subChild = NULL;
    Node *varNode = NULL;
    Types type = UNDEFINED , type2 = UNDEFINED;

    for (child = FIRSTCHILD(node); child != NULL; child = child->nextSibling) {
        if ((type = select_type(child->name)) == UNDEFINED){
            return 0;
        }
        // Add all child of type node to symbol table
        for (subChild = FIRSTCHILD(child); subChild != NULL; subChild = subChild->nextSibling){ 
            if (subChild->label == Assign) {
                // Variable declaration with initialization
                varNode = FIRSTCHILD(subChild);
                // If current variable is going to be assigned to another
                type2 = select_correct_type(global, local, SECONDCHILD(subChild));
                if (type2 == VOID_TYPE){
                    raise_sem_err(VOID_TYPE_AS_ASSIGNEMENT, SECONDCHILD(subChild));
                }
                if (type2 == UNDEFINED && SECONDCHILD(subChild)->label == Ident){
                    raise_sem_err(UNDECLARED, SECONDCHILD(subChild));
                } 
                if (type2 == INT_TYPE && type == CHAR_TYPE && !voidOperand){
                    // Case assignement to int variable with a char type value
                    print_warn(CHAR_EXPECTED, FIRSTCHILD(subChild));
                } else {
                    voidOperand = 0;
                }            
            } else {
             // Regular variable declaration
                varNode = subChild;
            }
            if (!add_symbol(local, varNode->name, type, NULL,NULL)){
                raise_sem_err(REDECLARED, varNode);
            }
            if(node->label == Parametres || node->label == DeclarVarGlob){
                local->nparam++;
            }
        }
    }
    return 1;
}

static int fill_local_sym_table(SymbolTable *global, SymbolTable *table, Node *node){
    // Do not build from null pointer table.
    if (!table){
        return 2;
    }
    Node *temp = THIRDCHILD(FIRSTCHILD(node));
    // Do not add parameter if there is none
    if (strcmp("void", FIRSTCHILD(temp)->name) != 0){
        add_variable(global, table, temp);
    }
    // Move to function's body if exists
    if (SECONDCHILD(node)) {
        temp = SECONDCHILD(node);
        // Get local variable nodes
        if (FIRSTCHILD(temp)->label == DeclarVarLoc) {
            // Fill table from variable declaration
            add_variable(global, table, FIRSTCHILD(temp));
        }
    }
    return 1;
}

static char * type_to_string(Types type){
    switch (type){
    case INT_TYPE:
        return "int";
        break;
    case CHAR_TYPE:
        return "char";
        break;
    case VOID_TYPE:
        return "void";
        break;
    default:
        return "undefined";
        break;
    }
}

static Node * build_tree(char * name , Types retype ,...){
    va_list args;
    Node * tmp = makeNode(DeclFonct);
    FIRSTCHILD(tmp) = makeNode(EnTeteFonct);
    FIRSTCHILD(FIRSTCHILD(tmp)) = makeNode(Type);
    FIRSTCHILD(FIRSTCHILD(tmp))->name = strdup(type_to_string(retype));
    SECONDCHILD(FIRSTCHILD(tmp)) = makeNode(Ident);
    SECONDCHILD(FIRSTCHILD(tmp))->name = strdup(name);
    THIRDCHILD(FIRSTCHILD(tmp)) = makeNode(Parametres);
    if (retype == VOID_TYPE){
        va_start(args, retype);
        Types tmp2 = va_arg(args, Types);
        FIRSTCHILD(THIRDCHILD(FIRSTCHILD(tmp))) = makeNode(Type);
        FIRSTCHILD(THIRDCHILD(FIRSTCHILD(tmp)))->name = strdup(type_to_string(tmp2));
        va_end(args);
    }else {
        FIRSTCHILD(THIRDCHILD(FIRSTCHILD(tmp))) = makeNode(Type);
        FIRSTCHILD(THIRDCHILD(FIRSTCHILD(tmp)))->name = strdup("void");
    }
    return tmp;
}

static void add_predefined_functions(SymbolTable * global){
    SymbolTable *tmp = (SymbolTable *)malloc(sizeof(SymbolTable));
    SymbolTable *tmp2 = (SymbolTable *)malloc(sizeof(SymbolTable));
    SymbolTable *tmp3 = (SymbolTable *)malloc(sizeof(SymbolTable));
    SymbolTable *tmp4 = (SymbolTable *)malloc(sizeof(SymbolTable));
    init_sym_table(&tmp);
    init_sym_table(&tmp2);
    add_symbol(tmp2, "c", CHAR_TYPE, NULL, NULL);
    tmp2->nparam++;
    init_sym_table(&tmp3);
    add_symbol(tmp3, "n", INT_TYPE, NULL, NULL);
    tmp3->nparam++;
    init_sym_table(&tmp4);
    add_symbol(global, "getint", INT_TYPE, tmp, build_tree("getint", INT_TYPE, VOID_TYPE));
    add_symbol(global, "putchar", VOID_TYPE, tmp2, build_tree("putchar", VOID_TYPE, CHAR_TYPE));
    add_symbol(global, "putint", VOID_TYPE, tmp3, build_tree("putint", VOID_TYPE, INT_TYPE));
    add_symbol(global, "getchar", CHAR_TYPE, tmp4, build_tree("getchar", CHAR_TYPE, VOID_TYPE));
}

static void set_sym_reladdr(SymbolTable *table){
    int i, start;
    if (table->size > 0){
        if (instance == GLOBAL){
            for (i = table->nparam - 1; i >= 0; i--){
                table->symbols[i].reladdr = table->total_bytes - i * 4 - 4;
            }
        } else if (instance == LOCAL) {
            start = table->nparam;
            for (i = start; i < table->size; i++){
                table->symbols[i].reladdr = (i - start) * 8 + 8;
            }
        }
    }
}

static int fill_global_sym_table(SymbolTable *table, Node *node){
    // Do not build from null pointer table.
    if (!table){
        return 2;
    }
    Node *child = NULL;
    Types type = UNDEFINED;
    SymbolTable *temp;
    // Get global variable nodes
    if (FIRSTCHILD(node)->label == DeclarVarGlob){
        // add all global variable found
        add_variable(NULL, table, FIRSTCHILD(node));
        // Function declarators must be second child
        child = SECONDCHILD(node);
    } else {
        // Function declarators must be first child in case no global variable
        child = FIRSTCHILD(node);
    }
    // Adding getint putchar
    add_predefined_functions(table);
    set_sym_reladdr(table);
    // Case no function declared isnt possible (Invalid program in case of no function declared)
    // Search among all existing functions
    instance = LOCAL;
    for (child = FIRSTCHILD(child); child != NULL; child = child->nextSibling){
        init_sym_table(&temp);
        if(!fill_local_sym_table(table, temp, child)){
            return 0;
        }
        set_sym_reladdr(temp);
        if ((type = select_type(FIRSTCHILD(FIRSTCHILD(child))->name)) == UNDEFINED){
            return 0;
        }
        if (!add_symbol(table, SECONDCHILD(FIRSTCHILD(child))->name, type, temp, child)){
            raise_sem_err(REDECLARED, SECONDCHILD(FIRSTCHILD(child)));
        }
        temp = NULL;
    }
    return 1;
}

void free_sym_table(SymbolTable **table){
    int i;
    SymbolTable *tmp;
    for (i = 0; i < (*table)->size; i++){
        free((*table)->symbols[i].name);
        // Case it is function symbol
        if ((*table)->symbols[i].table){
            tmp = (SymbolTable *)(*table)->symbols[i].table;
            free_sym_table(&tmp);
        }
    }
    free((*table)->symbols);
    free(*table);
    // Set to NULL after free 
    *table = NULL;
}

void print_symbol_table(const SymbolTable *table){
    static int init = 1;
    int i, j;
    char *name[MAX];
    void *array[MAX];
    j = 0;
    if (init){
        printf("\nglobal:\n");
        init = 0;
    }
    printf("=========== TABLE ==========\n");
    for (i = 0; i < table->size; i++){
        printf("type: %d | name: %s | table %p | reladdr: %d\n",
            table->symbols[i].type, table->symbols[i].name,
            table->symbols[i].table, table->symbols[i].reladdr);
        if (table->symbols[i].table){
            name[j] = table->symbols[i].name;
            array[j] = table->symbols[i].table;
            j++;
        }
    }
    printf("bytes: %d\n", table->total_bytes);
    putchar('\n');
    for (i = 0; i < j; i++){
        printf("\n%s:\n", name[i]);
        print_symbol_table((SymbolTable *) array[i]);
    }
}

static Err_c matching_return_value(Types retval, Node *node,
    SymbolTable *global, SymbolTable *local, Types *err){
    Symbol *tmp;
    int tmperr = 0;
    // Case no retval and there is a value on return token
    if (retval == VOID_TYPE) {
        if (FIRSTCHILD(node)){
            if (FIRSTCHILD(node)->label == Ident) {
                tmp = search_symbol(global, local, FIRSTCHILD(node)->name, NULL, NULL);
                if (tmp)
                    *err = tmp->type;
                else
                    return UNDECLARED;
                return RET_WITH_VALUE;
            }
            return RET_WITH_VALUE; 
        } else {
            return NO_ERR;
        }
    } // Case retval is an int, num token and int type indent are accepted 
    else if (retval == INT_TYPE){
        if (FIRSTCHILD(node)){
            // Verification required to check if ident is in table
            if (FIRSTCHILD(node)->label == Ident){
                tmp = search_symbol(global, local, FIRSTCHILD(node)->name, NULL, NULL);
                if (!tmp){
                    return UNDECLARED;
                }
                if (tmp->type == VOID_TYPE){
                    return VOID_TYPE_AS_RETVAL;
                }
            } else if (isOperand(FIRSTCHILD(node)) || isConditionalOperator(FIRSTCHILD(node))){
                checking_operand_format(global, local, FIRSTCHILD(node), &tmperr);
                if (tmperr){
                    return RET_WITH_NO_VALUE;
                }
            }
            // Char type indent are accepted
            return NO_ERR;
        } else {
            return RET_WITH_NO_VALUE;
        }
    } // Case retval is a char, only character token or char type indent are accepted 
    else {
        if (FIRSTCHILD(node)){
            if (FIRSTCHILD(node)->label == Num){
                *err = INT_TYPE;
                return CHAR_EXPECTED;
            } else if (FIRSTCHILD(node)->label == Ident){
                tmp = search_symbol(global, local, FIRSTCHILD(node)->name, NULL, NULL);
                if (tmp){
                    if (tmp->type == VOID_TYPE){
                        return VOID_TYPE_AS_RETVAL;
                    }
                    *err = tmp->type;
                } else {
                    return UNDECLARED;
                }
                if (*err == INT_TYPE){
                    *err = INT_TYPE;
                    return CHAR_EXPECTED;
                } else {
                    return NO_ERR;
                }
            } else {
                return RET_WITH_NO_VALUE;
            }
        } else {
            return RET_WITH_NO_VALUE;
        }
    }
}

static int is_func_sym(SymbolTable *global, Sym_scope scope, int index){
    if (scope == LOCAL){
        return 0;
    }
    return global->symbols[index].table != NULL;
}

static Err_c checking_ident_format(SymbolTable *global, SymbolTable *local, Node *node, Symbol *sym, int i, 
        Sym_scope scope){
    SymbolTable *table;
    if (FIRSTCHILD(node) && FIRSTCHILD(node)->label == Arguments && !is_func_sym(global, scope, i)){
        return VAR_AS_FUNC_CALL;
    } else if (FIRSTCHILD(node) && FIRSTCHILD(node)->label == Arguments && is_func_sym(global, scope, i)){
        // Call checkingArg
        table = (SymbolTable *)sym->table;
        check_argument(global, local, table, node, table->nparam);
        return NO_ERR;
    } else {
        return NO_ERR;
    }
}

static void sem_error_checking(SymbolTable *global, SymbolTable *local, Node *node, Types funcRetType){
    Err_c err;
    Sym_scope scope;
    Symbol *sym;
    int index;
    if(node->label == Ident){
        // Check if current ident node is declared in local table
        if(!(sym = search_symbol(global, local, node->name, &index, &scope))){
            raise_sem_err(UNDECLARED, node);
        } 
        // If current ident node has a child, it may be a function if it has arguments
        else if ((err = checking_ident_format(global, local, node, sym, index, scope)) != NO_ERR){
            raise_sem_err(err, node);
        }
    }
    if (node->label == Assign){
        // First child of node assign is always an ident and has a name
        Symbol *tmp1 = search_symbol(global, local, FIRSTCHILD(node)->name, NULL, NULL);
        // Case ident is a function name
        if (tmp1){
            if (tmp1->funcNode){
                raise_sem_err(FUNC_NAME_USED, FIRSTCHILD(node));
            } else {
                Types type2 = select_correct_type(global, local, SECONDCHILD(node));
                Types type1 = tmp1->type;
                if (type2 == VOID_TYPE || type1 == VOID_TYPE){
                    raise_sem_err(VOID_TYPE_AS_ASSIGNEMENT, SECONDCHILD(node));
                } else {
                    if (type2 == UNDEFINED && SECONDCHILD(node)->label == Ident){
                        raise_sem_err(UNDECLARED, SECONDCHILD(node));
                    } else if (type1 == CHAR_TYPE && type2 == INT_TYPE){
                        print_warn(CHAR_EXPECTED, FIRSTCHILD(node));
                    }
                }
            }
        } else {
            raise_sem_err(UNDECLARED, FIRSTCHILD(node));
        }
    }
    // If current node represents a return, compute checking with function type and return value
    if (node->label == _return_){
        Types retType = VOID_TYPE;
        Err_c err = matching_return_value(funcRetType, node, global, local, &retType);
        if (err == UNDECLARED){
            raise_sem_err(err, FIRSTCHILD(node));
        } else if (err == VOID_TYPE_AS_RETVAL) {
            raise_sem_err(err, FIRSTCHILD(node));
        } else if (err == RET_WITH_VALUE) {
            raise_sem_err(err, node);
        } else if (err == CHAR_EXPECTED) {
            print_warn(CHAR_EXPECTED, FIRSTCHILD(node));
        } else if (err != NO_ERR) {
            raise_sem_err(err, node);
        }
        hasReturn = 1;
    }
    // If token cannot take expression of void type such as function returning void
    if (node->label == _if_ || node->label == _while_){
        if (FIRSTCHILD(node)->label == Ident){
            if (select_correct_type(global, local, FIRSTCHILD(node)) == VOID_TYPE){
                raise_sem_err(VOID_TYPE_AS_OPERAND, FIRSTCHILD(node));
            }
        }
    }
    if (isOperand(node) || isConditionalOperator(node)){
        checking_operand_format(global, local, node, NULL);
    }
}

static void DFS_checking(SymbolTable *global, SymbolTable *local, Node *node, Types funcRetType){
    // Run through sub tree containing the body
    // and compute check for particular nodes
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling){
        sem_error_checking(global, local, child, funcRetType);
        DFS_checking(global, local, child, funcRetType);
    }
}

/**
 * @brief Returns body address node from
 * a starting point given
 * 
 * @param node starting point
 * @return Node* 
 */
static Node *move_to_body(Node *node){
    // From declfunct to body
    Node *tmp = node;
    if (!SECONDCHILD(node)) {
        return NULL;
    }
    tmp = SECONDCHILD(tmp);
    if(FIRSTCHILD(tmp)->label == DeclarVarLoc){
        return SECONDCHILD(tmp);
    } else {
        return FIRSTCHILD(tmp);
    }
}

/**
 * @brief Finds main function as symbol table
 * 
 * @param global Global symbol table
 * @param dest Destination's node pointer
 * @return int 
 */
int find_main(const SymbolTable *global, Node **dest){
    int i;
    for (i = 0; i < global->size; i++){
        if (strcmp(global->symbols[i].name, "main") == 0 && global->symbols[i].funcNode){
            (*dest) = global->symbols[i].funcNode;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Checks if main function is correctly defined
 * 
 * @param global Global symbol table
 */
static void check_main_state(const SymbolTable *global) {
    int found;
    Node *tmp = NULL;
    if (!(found = find_main(global, &tmp))){
        raise_sem_err(NO_MAIN, NULL);
    }
    if (found){
        char *type = FIRSTCHILD(FIRSTCHILD((tmp)))->name;
        if (select_type(type) != INT_TYPE){
            raise_sem_err(MAIN_WRONG_TYPE, NULL);
        }
    }
}

/**
 * @brief Compute all required checkings for each
 * functions found in the global table
 * 
 * @param global Global symbol table
*/
static void compute_checkings(SymbolTable *global){
    // Compute checking for each local function declared
    Symbol *funcSym = NULL;
    Node* body = NULL;
    Types rettype = UNDEFINED;
    for (int i = 0; i < global->size; i++){
        if(global->symbols[i].table != NULL){
            hasReturn = 0;
            funcSym = &global->symbols[i];
            rettype = funcSym->type;
            body = move_to_body(funcSym->funcNode);
            if (body){
                DFS_checking(global, funcSym->table, body, rettype);
            }
            if (!hasReturn && rettype != VOID_TYPE && body){
                raise_sem_err(RETURN_TOKEN_MISSING, body);
            }
        }
    }
    check_main_state(global);
}

/**
 * @brief Build all symbol tables of given tpc program
 * 
 * @param dest Destination pointer to retrieve symbol tables
 * @param root Starting point of tpc program
 * @return int
*/
int build_sym_tables(SymbolTable **dest, Node *root){
    // Initialize symbol table array
    SymbolTable *res = NULL;
    if (!init_sym_table(&res)){
        return 0;
    }
    // Add global function and deal with function declaration
    if (!fill_global_sym_table(res, root)){
        return 0;
    }
    // Compute semantic checkings in the current program
    compute_checkings(res);
    *dest = res;
    return 1;
}
