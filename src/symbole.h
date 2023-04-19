#ifndef __SYMBOLE__
#define __SYMBOLE__

#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define INIT_CAPACITY 16
#define MAX 512

#define ERR_REDEC_VAR "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 redeclaration of '%s' with no linkage.\n"                          \

#define ERR_UNDEC_VAR "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 '%s' undeclared (first use in this function)\n"                    \

#define ERR_VAR_TYPE_MISMATCH "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m: \
 incompatible types when assigning to type '%s' from type '%s'\n"            \

#define ERR_RETURN_MISMATCH "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 returning '%s' from a function with return type '%s'.\n"                 \

#define WARN_RETURN_MISMATCH "\033[1;35mWarning\033[0m \033[1;36ml:%d\033[0m:\
 returning '%s' from a function with return type '%s'.\n"                    \

#define WARN_RET_VOID_MISMATCH "\033[1;35mWarning\033[0m \033[1;36ml:%d\033[0m:\
 return with a value, in function returning void.\n"                           \
                                                                               \

#define ERR_FUNC_NAME_USED "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 '%s' is a function name. It cannot be assigned to any value.\n"        \

#define ERR_RET_VOID_MISMATCH "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 return with no value, in function returning non-void type.\n"              \

 #define ERR_FUNC_WRONG_USAGE "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 calling function '%s' without '()' token .\n" 

#define ERR_FUNC_ARG_NUMBER "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 wrong number arguments to function '%s'.\n" 

#define WARN_CHAR_ASSIGNEMENT "\033[1;35mWarning\033[0m \033[1;36ml:%d\033[0m:\
 '%s' is a char type but assignement is an int type .\n"            

#define WARN_EXPECTING_CHAR "\033[1;35mWarning\033[0m \033[1;36ml:%d\033[0m:\
 giving int type as argument to a function expecting char type.\n" 

#define ERR_MISSING_RET_TOKEN "\033[1;31mError\033[0m \033[1;36ml:%d\033[0m:\
 Current function is missing a return and doesnt return void type.\n"

#define ERR_NO_MAIN "\033[1;31mError\033[0m:\
 Main function not found.\n"

#define ERR_MAIN_WRONG_TYPE "\033[1;31mError\033[0m:\
 Main function return type is not int.\n"


extern int err_flag;

typedef enum types{
    INT_TYPE,
    CHAR_TYPE,
    VOID_TYPE,
    UNDEFINED /*inutile car comprit dans le lexeur */
} Types;

typedef enum err_c {
    UNDECLARED,
    REDECLARED,
    RET_WITH_NO_VALUE,
    RET_WITH_VALUE,
    FUNC_ARG_NUMBER,
    FUNC_NAME_USED,
    FUNC_WRONG_USAGE,
    CHAR_ASSIGNEMENT,
    CHAR_EXPECTED,
    RETURN_TOKEN_MISSING,
    NO_MAIN,
    MAIN_WRONG_TYPE,
    NO_ERR
} Err_c;

typedef struct Symbol{
    char *name;
    Types type;
    void *table;
    Node *funcNode;
} Symbol;

typedef struct SymbolTable{
    Symbol *symbols;
    int size;
    int capacity;
    unsigned int nparam;
    unsigned int total_bytes;
} SymbolTable;

int buildSymTables(SymbolTable **dest, Node *root);

void freeSymbolTable(SymbolTable **table);

void printSymbolTable(const SymbolTable *table);

void checkVariableDeclaration(SymbolTable *global ,Node *node);

int findMain(const SymbolTable *global, Node **dest);

#endif
