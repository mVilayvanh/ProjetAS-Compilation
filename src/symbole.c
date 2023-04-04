#include "symbole.h"

static const char * StringFromTypes[] = {
    "int",
    "char",
    "void",
    "UNDEFINED"
};

int hasReturn = 0;

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

static void addBytes(SymbolTable *table, Types type) {
    switch (type) {
        case INT_TYPE:
            table->total_bytes += 4;
            break;
        case CHAR_TYPE :
            table->total_bytes++;
            break;       
        default:
            break;
    }
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
    // Case it is a function and there is a table linked to this symbol
    if (ptr){
        table->symbols[table->size].table = ptr;
        table-> symbols[table->size].funcNode = funcNode;
    } else {
        addBytes(table, type);
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
            fprintf(stderr, ERR_REDEC_VAR, 
                SECONDCHILD(FIRSTCHILD(child))->lineno, 
                SECONDCHILD(FIRSTCHILD(child))->name);
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
    printf("bytes: %d\n", table->total_bytes);
    putchar('\n');
    for (i = 0; i < j; i++){
        printf("\n%s:\n", name[i]);
        printSymbolTable((SymbolTable *) array[i]);
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

static int nbParamFuncAsso(SymbolTable *table, Node *node){
    SymbolTable *temp = NULL;
    // Search among functions in global table 
    for(int i = 0 ; i < table->size ; i++){
        // If found in table, gets its number of parameter
        if(strcmp(table->symbols[i].name, node->name) == 0){
            temp =(SymbolTable *)(table->symbols[i].table);
            return temp->nparam;
        }
    }
    return 0;
}

static Types searchSymbolTypeInTable(SymbolTable *table, Node *node ){
    int i;
    for (i = 0; i < table->size; i++){
        if (strcmp(table->symbols[i].name, node->name) == 0){
            return table->symbols[i].type;
        }
    }
    return UNDEFINED;
}

static void sameTypeParameter(SymbolTable *table, Node *node, unsigned int nbParam){
    Node *child;
    Types type = UNDEFINED;
    int i = 0;
    // Compute type checking similarity between current function's node and parameters in function where
    // it is called
    for (child = node->firstChild; child != NULL && i < nbParam; child = child->nextSibling , i++){
        type = searchSymbolTypeInTable(table, child);
        if (type != UNDEFINED && table->symbols[i].type != type){
            fprintf(stderr, ERR_TYPE_MISMATCH,
                child->lineno, StringFromTypes[type],
                StringFromTypes[table->symbols[i].type]);
        }
    }
}

static int matchingReturnValue(Types retval, Node *node, SymbolTable *table, Types *err){
    // Checks if specified return node has the correct return value
    // void return value is not supposed to have any value
    // All good : 0; Void ret type something: 1, Mismatch type = 2
    if (retval == VOID_TYPE && FIRSTCHILD(node)) {
        if (FIRSTCHILD(node)->label == Ident) {
           *err = searchSymbolTypeInTable(table, FIRSTCHILD(node));
           if (*err == UNDEFINED)
                return 0;
           return 2;
        } 
        return 1;
    } else if (FIRSTCHILD(node)) {
        if (FIRSTCHILD(node)->label == Ident) {
            *err = searchSymbolTypeInTable(table, FIRSTCHILD(node));
            if (*err == UNDEFINED)
                return 0;
        }
        // Either it is a number, or it is an identificator with int type
        if (retval == INT_TYPE) {
            if (FIRSTCHILD(node)->label == Num){
                return 0;
            } else if (FIRSTCHILD(node)->label == Ident && *err == INT_TYPE){
                return 0;
            }
            return 2;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

static void checkingErrcode(int err, int lineno, Types funcRet, Types retType) {
    switch(err) {
        case 1:
            fprintf(stderr, ERR_RET_VOID_MISMATCH, lineno);
            break;
        case 2:
            fprintf(stderr, ERR_RETURN_MISMATCH,
                lineno, StringFromTypes[retType],
                StringFromTypes[funcRet]);
            break;
        default:
            break;
    }
}

static void variableInBody(SymbolTable *global, SymbolTable *local, Node *node, Types funcRetType){
    // Run through sub tree containing the body
    // and compute check for particular nodes
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling){
        if(child->label == Ident){
            // Check if current ident node is declared in local table
            if(searchSymbol(local, child->name) == 0){
                // May be in global table if not in local
                if(searchSymbol(global, child->name) == 0){
                   printErr(child->name, child->lineno, ERR_UNDECLARED);
                }
            } 
            // If current ident node has a child, it may be a function if it has arguments
            if(FIRSTCHILD(child) && FIRSTCHILD(child)->label == Arguments){
                sameTypeParameter(local, FIRSTCHILD(child), nbParamFuncAsso(global, child));       
            }
        }
        // If current node represents a return, compute checking with function type and return value
        if (child->label == _return_){
            Types retType = VOID_TYPE;
            int err = matchingReturnValue(funcRetType, child, local, &retType);
            checkingErrcode(err, child->lineno, funcRetType, retType);  
            if (!hasReturn)
                hasReturn = 1;
        }
        variableInBody(global, local, child, funcRetType);
    }
}


void checkVariableDeclaration(SymbolTable *global , Node *node){
    // Compute checking for each local function declared
    Symbol *funcSym = NULL;
    Types rettype = UNDEFINED;
    for (int i = 0; i < global->size; i++){
        if(global->symbols[i].table != NULL){
            funcSym = &global->symbols[i];
            rettype = searchSymbolTypeInTable(global, SECONDCHILD(FIRSTCHILD(funcSym->funcNode)));
            variableInBody(global, funcSym->table, funcSym->funcNode, rettype);
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
    *dest = res;
    return 1;
}


