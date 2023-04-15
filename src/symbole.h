#ifndef __SYMBOLE__
#define __SYMBOLE__

#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define INIT_CAPACITY 16
#define MAX 512

#define ERR_REDECLARED 0

#define ERR_UNDECLARED 1

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
 too many arguments to function '%s'.\n"       

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
    TYPE_MISMATCH,
    RET_WITH_NO_VALUE,
    RET_WITH_VALUE,
    RET_TYPE_MISMATCH,
    FUNC_ARG_NUMBER,
    FUNC_NAME_USED,
    FUNC_WRONG_USAGE,
    NO_ERR
} Err_c;

typedef struct Symbol{
    char *name;
    Types type;
    void *table;
    Node * funcNode ;
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

#endif
