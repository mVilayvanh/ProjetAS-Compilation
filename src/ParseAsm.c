#include "ParseAsm.h"


static void writeinit(FILE * f){
    if (f == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }
    fprintf(f, "global _start\n");
    fprintf(f, "extern show_registers\n");
    fprintf(f, "section .text\n");
    fprintf(f, "_start:\n");
}

static void writeend(FILE * f){
    fprintf(f, "\tmov rbx, rax\n\tcall show_registers\n");
    fprintf(f, "\tmov rax, 60\n\tmov rdi, 0\n\tsyscall\n");
    fclose(f);
}

static void writeLeaf(FILE *f, Node *leaf){
    if (leaf->isnum)
        fprintf(f, "\t; Add Leaf\n\tmov eax, %d\n\tpush rax\n", leaf->val);
    //else
        //fprintf(f, "\tmov eax, %s\n\tpush rax\n", leaf->name);
}

static void writeAddSub(FILE * f, Node *node){
    if (strcmp("+", node->name) == 0){
        fprintf(f, 
        "\t; Compute add\n\tpop rcx\n\tpop rax\n\tadd rax, rcx\n\tpush rax\n");
    } 
    else {
        fprintf(f,
            "\t; Compute sub\n\tpop rcx\n\tpop rax\n\tsub rax, rcx\n\tpush rax\n");
    }
}


static void writeMul(FILE * f, Node *node){
    fprintf(f,
        "\t; Compute Mul\n\tpop rcx\n\tpop rax\n\timul rax, rcx\n\tpush rax\n");
}

static void writeExpr(FILE *f, Node *node){
    switch (node->label){
        case Num:
            writeLeaf(f, node);
            break;
        case Addsub:
            writeAddSub(f, node);
            break;
        case Divstar:
            writeMul(f, node);
            break;
        default:
            fprintf(stderr, "Should not be here\n");
            break;
    }
    node->visited = 1;
}

static int BothChildAreNum(Node *node){
    return FIRSTCHILD(node) && FIRSTCHILD(node)->label == Num
        && SECONDCHILD(node) && SECONDCHILD(node)->label == Num;
}

static void translateExprToAsm(FILE * f, Node *node){
    // Left child = FIRST CHILD
    // Right child = NEXT SIBLING
    if (node){
        // Means that operation has to be applied
        if (BothChildAreNum(node)){
            writeExpr(f, FIRSTCHILD(node));
            writeExpr(f, SECONDCHILD(node));
            writeExpr(f, node);
        } else {
            // case to fix later
            if (node->label == Ident){
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
static int isoperand(Node *node){
    return node->label == Addsub || node->label == Divstar ;
}

static void searchop(FILE *f, Node *node){
    for (Node *child = FIRSTCHILD(node); child != NULL; child = child->nextSibling) {
        if(isoperand(child) && !child->visited){
            translateExprToAsm(f, child);
        }
        searchop(f, child);
    } 
     
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
}

