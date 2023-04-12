#include "ParseAsm.h"
#include <stdarg.h>

char buffer[BUFFERSIZE] = "";

static void writeOnBuffer(FILE *f, char *suffix, ...){
    char tmp[BUFFERSIZE] = "";
    va_list list;
    if (strlen(buffer) + strlen(suffix) >= BUFFERSIZE) {
        fprintf(f, buffer);
        // reset buffer
        buffer[0] = '\0';
    }
    
    va_start(list, suffix);
    vsprintf(tmp, suffix, list);
    va_end(list);
    strcat(buffer, tmp);
}

static void writeinit(FILE * f){
    if (f == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }
    
    writeOnBuffer(f, "global _start\n");
    writeOnBuffer(f, "extern show_registers\n");
    writeOnBuffer(f, "section .text\n");
    writeOnBuffer(f, "_start:\n");
}

static void writeend(FILE * f){
    writeOnBuffer(f, "\tmov rbx, rax\n\tcall show_registers\n");
    writeOnBuffer(f, "\tmov rax, 60\n\tmov rdi, 0\n\tsyscall\n");
}

static void writeLeaf(FILE *f, Node *leaf){
    switch(leaf->label) {
        case Num:
            writeOnBuffer(f, "\t; Add Leaf\n\tmov eax, %d\n\tpush rax\n", leaf->val);
            break;
        case Character:
            // Since Characters are only of size 1 + \0, retriving respectif ascii value
            writeOnBuffer(f, "\t; Add Leaf\n\tmov eax, %d\n\tpush rax\n", leaf->name[1] - 0);
            break;
        case Ident:
            // Case to set later
            // Not sure yet how it will be implemented but expecting it to be on stack
            break;
        default:
            break;
    } 
    
}

static void writeAddSub(FILE * f, Node *node){
    if (strcmp("+", node->name) == 0){
        writeOnBuffer(f, 
        "\t; Compute add\n\tpop rcx\n\tpop rax\n\tadd rax, rcx\n\tpush rax\n");
    } 
    else {
        writeOnBuffer(f,
            "\t; Compute sub\n\tpop rcx\n\tpop rax\n\tsub rax, rcx\n\tpush rax\n");
    }
}


static void writeDivstar(FILE * f, Node *node){
    if (strcmp(node->name, "*") == 0) {
        writeOnBuffer(f,
                "\t; Compute Mul\n\tpop rcx\n\tpop rax\n\timul rax, rcx\n\tpush rax\n");
    } else {
         writeOnBuffer(f,
                "\t; Compute Div\n\tpop rcx\n\tpop rax\n\tidiv rcx\n\tpush rax\n");
    }
}

static void writeExpr(FILE *f, Node *node){
    switch (node->label){
        case Num:
            writeLeaf(f, node);
            break;
        case Character:
            writeLeaf(f, node); break;
        case Addsub:
            writeAddSub(f, node);
            break;
        case Divstar:
            writeDivstar(f, node);
            break;
        default:
            fprintf(stderr, "Should not be here\n");
            break;
    }
    node->visited = 1;
}

static int bothChildAreNum(Node *node){
    return FIRSTCHILD(node) && FIRSTCHILD(node)->label == Num
        && SECONDCHILD(node) && SECONDCHILD(node)->label == Num;
}

static int bothChildAreChar(Node *node){
    return FIRSTCHILD(node) && FIRSTCHILD(node)->label == Character
        && SECONDCHILD(node) && SECONDCHILD(node)->label == Character;
}

static int bothChildArePrimitive(Node *node){
    return bothChildAreNum(node) || bothChildAreChar(node);
}

static void translateExprToAsm(FILE * f, Node *node){
    // Left child = FIRST CHILD
    // Right child = NEXT SIBLING
    if (node){
        // Means that operation has to be applied
        if (bothChildArePrimitive(node)){
            writeExpr(f, FIRSTCHILD(node));
            writeExpr(f, SECONDCHILD(node));
            writeExpr(f, node);
        } else {
            // case to fix later
            if (node->label == Ident){
                return;
            
            }
            if (node->label == Character){
                writeExpr(f, node);
                return;
            }
            if (node->label == Num){
                writeExpr(f, node);
                return;
            }
            translateExprToAsm(f, FIRSTCHILD(node));
            translateExprToAsm(f, SECONDCHILD(node));
            writeExpr(f, node);
        }
    }
}

static int find_Main(const SymbolTable *global, Node **dest ){
    int i;
    for (i = 0; i < global->size; i++){
        if (strcmp(global->symbols[i].name, "main") == 0){
            (*dest) = global->symbols[i].funcNode;
            return 1;
        }
    }
    return 0;
}

static void moveRootToSuitInstr(Node *root){
    root = SECONDCHILD(root);
    if(FIRSTCHILD(root)->label == DeclarVarLoc){
        root = SECONDCHILD(root);
    }else{
        root = FIRSTCHILD(root);
    }
}

static void searchop(FILE *f, Node *node){
    for (Node *child = FIRSTCHILD(node); child != NULL; child = child->nextSibling) {
        if(isOperand(child) && !child->visited){
            translateExprToAsm(f, child);
        }
        searchop(f, child);
    } 
     
}


void writeWhile(){

}

void writeAsm(SymbolTable * global){
    Node * temp = NULL;
    if (!find_Main(global, &temp)){
        printf("Erreur : Fonction main non déclarée");
        return;
    } 
    FILE * f = fopen("ano.asm", "w");
    writeinit(f);
    moveRootToSuitInstr(temp);
    searchop(f, temp);
    writeend(f);
    fprintf(f, buffer);
    fclose(f);
}

