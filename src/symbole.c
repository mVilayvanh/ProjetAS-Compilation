#include "symbole.h"

#include <stdarg.h>

int hasReturn = 0;

static Symbol *searchSymbol(SymbolTable *global, SymbolTable *local, char *name){
    int i;
    if (local) {
        for (i = 0; i < local->size; i++){
            if (strcmp(local->symbols[i].name, name) == 0){
                return &(local->symbols[i]);
            }
        }
    }
    if (global) {
        for (i = 0; i < global->size; i++){
            if (strcmp(global->symbols[i].name, name) == 0){
                return &(global->symbols[i]);
            }
        } 
    }
    return NULL;
}

static void printWarn(Err_c  code , Node * node , ...){
    switch (code){
        case RET_WITH_VALUE:
            fprintf(stderr, WARN_RET_VOID_MISMATCH, node->lineno);
            break;
        case CHAR_ASSIGNEMENT:
            fprintf(stderr, WARN_CHAR_ASSIGNEMENT, node->lineno, node->name);
            break;
        case CHAR_EXPECTED:
            fprintf(stderr, WARN_EXPECTING_CHAR, node->lineno);
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
        default:
            break;
    }
}

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

static int nbParamFuncAsso(SymbolTable *table, char *name){
    SymbolTable *temp = NULL;
    // Search among functions in global table 
    for(int i = 0 ; i < table->size ; i++){
        // If found in table, gets its number of parameter
        if(strcmp(table->symbols[i].name, name) == 0){
            temp =(SymbolTable *)(table->symbols[i].table);
            return temp->nparam;
        }
    }
    return 0;
}

static int countArgument(Node * node){
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

static int checkIsFunction(SymbolTable *global ,Node *node){
    Symbol *tmp;
     if((tmp = searchSymbol(global, NULL, node->name))){
        if (tmp && tmp->funcNode != NULL){
            return 1;
        }
    }
    return 0;
}

static int checkArgument(SymbolTable *global, SymbolTable *local, SymbolTable *funcTable,
        Node *node, unsigned int nbParam){
    Node *child ,*arguments;
    Symbol *tmp;
    Types type = UNDEFINED;
    int i = 0;
    // Compute type checking similarity between current function's node and parameters in function where
    // it is called
    if(FIRSTCHILD(node) == NULL){
        raise_sem_err(FUNC_WRONG_USAGE, node);
        return 1;
    }
    arguments = FIRSTCHILD(node);
    
    for (child = arguments->firstChild; child != NULL && i < nbParam; child = child->nextSibling , i++){
        if (child->label == Ident){
            tmp = searchSymbol(global, local, child->name);
            // is function
            if (tmp && tmp->funcNode) {
                int err = checkArgument(global, local, tmp->table, child, nbParamFuncAsso(global, tmp->name));
                if (err){
                    // Jsp pour l'instant printf("err recursive\n");
                }
            }
            // Not found
            if (!tmp){
                raise_sem_err(UNDECLARED, child);
                return 1;
            }
            type = tmp->type;
        } else if (child->label == Num) {
            type = INT_TYPE;
        } else if (child->label == Character) {
            type = CHAR_TYPE;
        }
        
        if (type != UNDEFINED && funcTable->symbols[i].type == CHAR_TYPE && type == INT_TYPE){
            printWarn(CHAR_EXPECTED, child);
        } 
    }
    if (countArgument(arguments) != nbParam){
        raise_sem_err(FUNC_ARG_NUMBER, node);
    }
    return 0;
}

static Types selectCorectType(SymbolTable *global, SymbolTable *local , Node *node){
    Types res = UNDEFINED;
    Symbol *tmp;
    switch (node->label){
    case Num:
        res = INT_TYPE;
        break;
    case Character:
        res = CHAR_TYPE;
        break;
    case Ident:
        tmp = searchSymbol(global, local, node->name);
        if (tmp && tmp->funcNode == NULL){
            res = tmp->type;
        }
        else if (tmp && tmp->funcNode != NULL){
            if(checkArgument(global, local, tmp->table, node, nbParamFuncAsso(global, node->name)) == 0)
                res = tmp->type;
            else
                res = UNDEFINED;
        }else
            res = UNDEFINED;
        break;

    case Addsub :
        res = INT_TYPE;
        break;
    case Divstar :
        res = INT_TYPE;
        break;
    default:
        break;
    }
    return res;
}

static int addVariable(SymbolTable *global, SymbolTable *local, Node *node){
    Node *child = NULL;
    Node *subChild = NULL;
    Node *varNode = NULL;
    Types type = UNDEFINED , type2 = UNDEFINED;

    for (child = FIRSTCHILD(node); child != NULL; child = child->nextSibling) {
        if ((type = selectType(child->name)) == UNDEFINED){
            return 0;
        }
        // Add all child of type node to symbol table
        for (subChild = FIRSTCHILD(child); subChild != NULL; subChild = subChild->nextSibling){ 
            if (subChild->label == Assign) {
                // Variable declaration with initialization
                varNode = FIRSTCHILD(subChild);
                // If current variable is going to be assigned to another
                type2 = selectCorectType(global, local, SECONDCHILD(subChild));
                if (type2 == UNDEFINED && SECONDCHILD(subChild)->label == Arguments && !checkIsFunction(global ,SECONDCHILD(subChild ))){
                    raise_sem_err(UNDECLARED, SECONDCHILD(subChild));
                }else if(type2 == INT_TYPE && type == CHAR_TYPE){
                    // Ajouter cas fonction affectée

                    // Case assignement to int variable with a char type value
                    printWarn(CHAR_ASSIGNEMENT, FIRSTCHILD(subChild));
                }            
            } else {
             // Regular variable declaration
                varNode = subChild;
            }
            if (!addSymbol(local, varNode->name, type, NULL,NULL)){
                raise_sem_err(REDECLARED, varNode);
            }
            if(node->label == Parametres){
                local->nparam++;
            }
        }
    }
    return 1;
}

static int fillLocalSymbolTable(SymbolTable *global, SymbolTable *table, Node *node){
    // Do not build from null pointer table.
    if (!table){
        return 2;
    }
    Node *temp = THIRDCHILD(FIRSTCHILD(node));
    // Do not add parameter if there is none
    if (strcmp("void", FIRSTCHILD(temp)->name) != 0){
        addVariable(global, table, temp);
    }
    // Move to function's body if exists
    if (SECONDCHILD(node)) {
        temp = SECONDCHILD(node);
        // Get local variable nodes
        if (FIRSTCHILD(temp)->label == DeclarVarLoc) {
            // Fill table from variable declaration
            addVariable(global, table, FIRSTCHILD(temp));
        }
    }
    return 1;
}

/*
static void addGetFunc(SymbolTable *global, Types retval, Types parameter_t){
    Node *func_start = makeNode(DeclFonct);
}
*/

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
        addVariable(NULL, table, FIRSTCHILD(node));
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
        if(!fillLocalSymbolTable(table, temp, child)){
            return 0;
        }
        if ((type = selectType(FIRSTCHILD(FIRSTCHILD(child))->name)) == UNDEFINED){
            return 0;
        }
        if (!addSymbol(table, SECONDCHILD(FIRSTCHILD(child))->name, type, temp, child)){
            raise_sem_err(REDECLARED, SECONDCHILD(FIRSTCHILD(child)));
        }
        temp = NULL;
    }
    // Adding getint putchar
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



static Err_c matchingReturnValue(Types retval, Node *node,
    SymbolTable *global, SymbolTable *local, Types *err){
    Symbol *tmp;
    // Case no retval and there is a value on return token
    if (retval == VOID_TYPE) {
        if (FIRSTCHILD(node)){
            if (FIRSTCHILD(node)->label == Ident) {
                tmp = searchSymbol(global, local, FIRSTCHILD(node)->name);
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
            if (FIRSTCHILD(node)->label == Ident && !searchSymbol(global, local, FIRSTCHILD(node)->name)){
                return UNDECLARED;    
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
                return CHAR_ASSIGNEMENT;
            } else if (FIRSTCHILD(node)->label == Ident){
                tmp = searchSymbol(global, local, FIRSTCHILD(node)->name);
                if (tmp){
                    *err = tmp->type;
                } else {
                    return UNDECLARED;
                }
                if (*err == INT_TYPE){
                    *err = INT_TYPE;
                    return CHAR_ASSIGNEMENT;
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

static void sem_error_checking(SymbolTable *global, SymbolTable *local, Node *node, Types funcRetType){
    if(node->label == Ident){
        Symbol *tmp;
        // Check if current ident node is declared in local table
        tmp = searchSymbol(global, local, node->name);
        if (!tmp) {
            //raise_sem_err(UNDECLARED, node);
        } else {
            // If current ident node has a child, it may be a function if it has arguments
            if(FIRSTCHILD(node) && FIRSTCHILD(node)->label == Arguments){
                // Peut y avoir une zone a risque
                selectCorectType(global, local, FIRSTCHILD(node));       
            }
        }
    }
    if (node->label == Assign){
        // First child of node assign is always an ident and has a name
        Symbol *tmp1 = searchSymbol(global, local, FIRSTCHILD(node)->name);
        // Case ident is a function name
        if (tmp1){
            if (tmp1->funcNode){
                raise_sem_err(FUNC_NAME_USED, FIRSTCHILD(node));
            } else {

                // A regler, ne doit pas lire le type d'une fonction
                Types type2 = selectCorectType(global, local, SECONDCHILD(node));
                Types type1 = tmp1->type;
                if (type1 != type2 && type1 != UNDEFINED && type2 != UNDEFINED){
                    // Case assignement to int variable with a char type value    
                    if (type1 == CHAR_TYPE && type2 == INT_TYPE){
                        printWarn(CHAR_ASSIGNEMENT, node);
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
        Err_c err = matchingReturnValue(funcRetType, node, global, local, &retType);
        if (err == UNDECLARED){
            raise_sem_err(UNDECLARED, FIRSTCHILD(node));
        } else if (err == RET_WITH_VALUE) {
            printWarn(err, node);
        } else if (err != NO_ERR) {
            raise_sem_err(err, node);
        }
        if (err == NO_ERR || (err == RET_WITH_NO_VALUE && funcRetType == VOID_TYPE) || err == RET_WITH_VALUE) {
            hasReturn = 1;
        }
    }
}

static void variableInBody(SymbolTable *global, SymbolTable *local, Node *node, Types funcRetType){
    // Run through sub tree containing the body
    // and compute check for particular nodes
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling){
        sem_error_checking(global, local, child, funcRetType);
        variableInBody(global, local, child, funcRetType);
    }
}

static Node * moveToBody(Node *node){
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

int findMain(const SymbolTable *global, Node **dest){
    int i;
    for (i = 0; i < global->size; i++){
        if (strcmp(global->symbols[i].name, "main") == 0 && global->symbols[i].funcNode){
            (*dest) = global->symbols[i].funcNode;
            return 1;
        }
    }
    return 0;
}

static void checkMainState(const SymbolTable *global, Node **dest) {
    int found;
    if (!(found = findMain(global, dest))){
        raise_sem_err(NO_MAIN, NULL);
    }
    if (found){
        char *type = FIRSTCHILD(FIRSTCHILD((*dest)))->name;
        if (selectType(type) != INT_TYPE){
            raise_sem_err(MAIN_WRONG_TYPE, NULL);
        }
    }
}

void checkVariableDeclaration(SymbolTable *global, Node *node){
    // Compute checking for each local function declared
    Symbol *funcSym = NULL;
    Node *dummy, *body = NULL;
    Types rettype = UNDEFINED;
    for (int i = 0; i < global->size; i++){
        if(global->symbols[i].table != NULL){
            hasReturn = 0;
            funcSym = &global->symbols[i];
            rettype = funcSym->type;
            body = moveToBody(funcSym->funcNode);
            if (body){
                variableInBody(global, funcSym->table, body, rettype);
            }
            if (!hasReturn && rettype != VOID_TYPE && body){
                raise_sem_err(RETURN_TOKEN_MISSING, body);
            }
        }
    }
    checkMainState(global, &dummy);
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

