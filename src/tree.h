/* tree.h */
#ifndef __TREE__
#define __TREE__


#define FOREACH_LABEL(LABEL)    \
    LABEL(Prog)                 \
    LABEL(DeclarVarGlob)        \
    LABEL(DeclFoncts)           \
    LABEL(DeclarateursGlob)     \
    LABEL(DeclFonct)            \
    LABEL(EnTeteFonct)          \
    LABEL(Corps)                \
    LABEL(Parametres)           \
    LABEL(DeclarVarLoc)         \
    LABEL(SuiteInstr)           \
    LABEL(Exp)                  \
    LABEL(Num)                  \
    LABEL(Character)            \
    LABEL(Arguments)            \
    LABEL(Ident)                \
    LABEL(Type)                 \
    LABEL(UnaryAddsub)          \
    LABEL(Addsub)               \
    LABEL(Divstar)              \
    LABEL(Order)                \
    LABEL(Eq)                   \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum LABEL_ENUM{
    /* list all other node labels, if any */
    /* The list must coincide with the string array in tree.c */
    /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
    FOREACH_LABEL(GENERATE_ENUM)
    Assign,
    _else_,
    _if_,
    _while_,
    _return_,
    and,
    or,
    not
} label_t;

typedef struct Node {
    char isnum;
    label_t label;
    int val;
    int lineno;
    int visited;
    char *name;
    struct Node *firstChild, *nextSibling;
} Node;

extern int lineno;       /* from lexer */

Node *makeNode(label_t label);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);
int isOperand(Node *node);
int isOrderOrEqual(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define NEXTSIBLING(node) node->nextSibling
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling

#endif
