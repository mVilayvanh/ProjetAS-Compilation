#include "symbole.h"
static const char * StringFromTypes[] = {
    "int",
    "char",
    "void",
    "UNDEFINED"
};

static int initSymbolTable(SymbolTable **dest){
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

    void c_To_Asm(FILE *f, SymbolTable SymbolTable){
        /* faire les soustractions dans la pile de c à asm */
        f = fopen("ano.asm", "w");

    }
        
static int addSymbol(SymbolTable *table, char *name, Types type, SymbolTable *ptr, Node *funcNode){
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
        table->symbols = realloc(table->symbols, table->capacity * sizeof(Symbol *));
    }
    // Initialise les autres champs du symbole selon les besoins
    table->symbols[table->size].name = strdup(name);
    table->symbols[table->size].type = type; 
    if (ptr){
        table->symbols[table->size].table = ptr;
        table-> symbols[table->size].funcNode = funcNode;
    }
    table->size++;
    return 1;
}

static int selectType(char *name){
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

static int addVariable(SymbolTable *table, Node *node){
    Node *child = NULL;
    Node *subChild = NULL;
    Node *varNode = NULL;
    Types type = UNDEFINED;

    for (child = FIRSTCHILD(node); child != NULL; child = child->nextSibling) {
        if ((type = selectType(child->name)) == UNDEFINED){
            return 0;
        }
        // Add all child of type node to symbol table
        for (subChild = FIRSTCHILD(child); subChild != NULL; subChild = subChild->nextSibling){ 
            if (subChild->label == Assign) {
                // Variable declaration with initialization
                varNode = FIRSTCHILD(subChild);
            } else {
                // Regular variable declaration
                varNode = subChild;
            }
            if (!addSymbol(table, varNode->name, type, NULL,NULL)){
                fprintf(stderr, ERR_REDEC_VAR, varNode->lineno, varNode->name);
            }
            if(node->label == Parametres){
                table->nparam++;
            }
        }
    }
    return 1;
}


static int fillLocalSymbolTable(SymbolTable *table, Node *node){
    // Do not build from null pointer table.
    if (!table){
        return 2;
    }
    Node *temp = THIRDCHILD(FIRSTCHILD(node));
    // Do not add parameter if there is none
    if (strcmp("void", FIRSTCHILD(temp)->name) != 0){
        addVariable(table, temp);
    }
    // Move to function's body
    temp = SECONDCHILD(node);
    // Get local variable nodes
    if (FIRSTCHILD(temp)->label == DeclarVarLoc) {
        // Fill table from variable declaration
        addVariable(table, FIRSTCHILD(temp));
    }

    return 1;
}

static int fillGlobalSymbolTable(SymbolTable *table, Node *node){
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
        addVariable(table, FIRSTCHILD(node));
        // Function declarators must be second child
        child = SECONDCHILD(node);
    } else {
        // Function declarators must be first child in case no global variable
        child = FIRSTCHILD(node);
    }
    // Case no function declared isnt possible (Invalid program in case of no function declared)
    // Search among all existing functions
    for (child = FIRSTCHILD(child); child != NULL; child = child->nextSibling){
        initSymbolTable(&temp);
        if(!fillLocalSymbolTable(temp, child)){
            return 0;
        }
         if ((type = selectType(FIRSTCHILD(FIRSTCHILD(child))->name)) == UNDEFINED){
            return 0;
        }
        if (!addSymbol(table, SECONDCHILD(FIRSTCHILD(child))->name, type, temp, child)){
            fprintf(stderr, ERR_REDEC_VAR, SECONDCHILD(FIRSTCHILD(child))->lineno, SECONDCHILD(FIRSTCHILD(child))->name);
        }
        temp = NULL;
    }
    return 1;
}

void freeSymbolTable(SymbolTable **table){
    int i;
    SymbolTable *tmp;
    for (i = 0; i < (*table)->size; i++){
        // Case it is function symbol
        if ((*table)->symbols[i].table){
            tmp = (SymbolTable *)(*table)->symbols[i].table;
            freeSymbolTable(&tmp);
        }
    }
    // Free symbol names
    for (i = 0; i < (*table)->size; i++){
        free((*table)->symbols[i].name);
    }
    free((*table)->symbols);
    free(*table);
    // Set to NULL after free 
    *table = NULL;
}

void printSymbolTable(const SymbolTable *table){
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
        printf("type: %d | name: %s | table %p\n",
            table->symbols[i].type, table->symbols[i].name,
            table->symbols[i].table);
        if (table->symbols[i].table){
            name[j] = table->symbols[i].name;
            array[j] = table->symbols[i].table;
            j++;
        }
    }
    putchar('\n');
    for (i = 0; i < j; i++){
        printf("\n%s:\n", name[i]);
        printSymbolTable((SymbolTable *) array[i]);
    }
}



static void sumbytes(SymbolTable * global){
    int i ;
    for(i = 0 ; i < global->size;i++){
        if(global-> symbols[i].table == NULL){
            switch (global->symbols[i].type)
            {
            case INT_TYPE:
                global->total_bytes += 4;
                break;
            case CHAR_TYPE :
                global->total_bytes++;
                break;       
            default:
                break;
            }
        } 
    }
}

static int searchSymbol(SymbolTable *table, char *name){
    int i;
    for (i = 0; i < table->size; i++){
        if (strcmp(table->symbols[i].name, name) == 0){
            return 1;
        }
    }
    return 0;
}


static int nbParamFuncAsso(SymbolTable *table , Node *node){
    SymbolTable * temp = NULL;
    for(int i = 0 ; i < table->size ; i++){
        if(strcmp(table->symbols[i].name,node->name) == 0){
            temp =(SymbolTable *)(table->symbols[i].table);
            return temp->nparam;
        }
    }
    return 0 ;
}

static Types searchSymbolInTable(SymbolTable *table, Node *node ){
    for (int i = 0; i < table->size; i++){
        if (strcmp(table->symbols[i].name, node->name) == 0){
            return table->symbols[i].type;
        }
    }
    return UNDEFINED;
}

static int sameTypeParameter(SymbolTable *table, Node *node, unsigned int nbParam){
    Node * child ;
    Types type = UNDEFINED;
    int i = 0 ;
   for (child = node->firstChild; child != NULL && i < nbParam; child = child->nextSibling , i++){
        type = searchSymbolInTable(table, child);
        if (type != UNDEFINED){
            if(table->symbols[i].type != type){
                fprintf(stderr,ERR_TYPE_MISMATCH,
                    child->lineno,StringFromTypes[type],
                    StringFromTypes[table->symbols[i].type]);
            }
        }
    }
    return 1;
}

static int variableInBody(SymbolTable *global, SymbolTable *local, Node *node){
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling){
        if(child->label == Ident){
            if(searchSymbol(local, child->name) == 0){
                if(searchSymbol(global, child->name) == 0){
                   printErr(child->name, child->lineno, ERR_UNDECLARED);
                }
            } 
            if(FIRSTCHILD(child) && FIRSTCHILD(child)->label == Arguments){
                sameTypeParameter(local, FIRSTCHILD(child), nbParamFuncAsso(global, child));       
            }
        }
        variableInBody(global, local, child);
    }
    return 1 ;
}


void checkVariableDeclaration(SymbolTable *global , Node *node){
    for (int i = 0; i < global->size; i++){
        if(global->symbols[i].table != NULL){
            variableInBody(global, global->symbols[i].table, global->symbols[i].funcNode);
        }
    }   
}

int buildSymTables(SymbolTable **dest, Node *root){
    // Initialize symbol table array
    SymbolTable *res = NULL;
    if (!initSymbolTable(&res)){
        return 0;
    }
    // Add global function and deal with function declaration
    if (!fillGlobalSymbolTable(res, root)){
        return 0;
    }
    // Compute identificator checking in the current program
    checkVariableDeclaration(res, root);
    // Count how much bytes weight all variables
    sumbytes(res);
    *dest = res;
    return 1;
}


