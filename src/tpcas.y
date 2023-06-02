
%{
/* Parseur du projet tpc */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "Format.h"
#include "symbole.h"
#include "ParseAsm.h"

int yyerror(char *msg);
int yylex(void);
int yyparse();

extern int lineno;
extern int errorinline;
char name[64];

int help_flag = 0;
int tree_flag = 0;
int sym_flag = 0;
int varGlob_flag = 0;
int varLoc_flag = 0;
int suiteInstr_flag = 0;
int err_flag = 0;

%}

%union {
    Node* node;
    char byte[5];
    int num;
    char type[6];
    char ident[64];
    char comp[3];
}

%token <type> TYPE VOID IF ELSE WHILE RETURN OR AND ORDER EQ   
%token <ident> IDENT
%token <num> NUM
%token <byte> CHARACTER ADDSUB DIVSTAR

%type <node> Prog DeclarVarGlob DeclFoncts DeclarateursGlob DeclFonct EnTeteFonct Corps Parametres LValue Arguments ListExp  Instr  
%type <node> ListTypVar DeclarVarLoc SuiteInstr DeclarateursLoc Affectation Exp TB FB M E T F

%right THEN ELSE

%%

Prog:  DeclarVarGlob DeclFoncts {
                                    SymbolTable *table = NULL;
                                    $$ = makeNode(Prog);
                                    if (varGlob_flag){
                                        addChild($$, $1);
                                        addSibling($1, $2);
                                    } else {
                                        deleteTree($1);
                                        addChild($$, $2);
                                    }
                                    // Construction table des symboles
                                    build_sym_tables(&table, $$);
                                    if (tree_flag){
                                        printTree($$);
                                    }
                                    if (sym_flag){
                                        print_symbol_table(table);
                                    }
                                    // Construction code assembleur
                                    if (!err_flag){
                                        write_Asm(table);
                                    }
                                    free_sym_table(&table);
                                    deleteTree($$);
                                }
    ;
DeclarVarGlob:
       DeclarVarGlob TYPE DeclarateursGlob ';' {    
                                                    if (!varGlob_flag)
                                                        varGlob_flag = 1;
                                                    Node *child;
                                                    child = makeNode(Type);
                                                    child->name = strdup($2);
                                                    addChild($1, child);
                                                    addChild(child, $3);
                                                }
    |                                           {
                                                    $$ = makeNode(DeclarVarGlob);
                                                }
    ;
DeclarateursGlob:
       DeclarateursGlob ',' IDENT               {               
                                                    Node * child = makeNode(Ident);
                                                    child->name = strdup($3);
                                                    addSibling($1, child);
                                                }
    |  IDENT                                    {               
                                                    $$ = makeNode(Ident);
                                                    $$->name = strdup($1);
                                                }
    ;
DeclFoncts:
       DeclFoncts DeclFonct                     {
                                                    $$ = $1;
                                                    addChild($$, $2);
                                                }
    |  DeclFonct                                {
                                                    $$ = makeNode(DeclFoncts);
                                                    addChild($$, $1);
                                                }
    ;
DeclFonct:
       EnTeteFonct Corps                        {
                                                    $$ = makeNode(DeclFonct);
                                                    addChild($$, $1);
                                                    addSibling($1, $2);
                                                }
    ;
EnTeteFonct:
       TYPE IDENT '(' Parametres ')'            {    

                                                    $$ = makeNode(EnTeteFonct);
                                                    Node *child1 , *child2;
                                                    child1 = makeNode(Type);
                                                    child1->name = strdup($1);
                                                    addChild($$, child1);
                                                    child2 = makeNode(Ident);
                                                    child2->name = strdup($2);
                                                    addSibling(child1, child2);
                                                    addSibling(child2, $4);
                                                }
    |  VOID IDENT '(' Parametres ')'            {   
                                                    $$ = makeNode(EnTeteFonct);
                                                    Node *child1, *child2;
                                                    child1 = makeNode(Type);
                                                    child1->name = strdup($1);
                                                    child2 = makeNode(Ident);
                                                    addChild($$, child1);
                                                    child2->name = strdup($2);
                                                    addSibling(child1, child2);
                                                    addSibling(child2, $4);
                                                }
    ;
Parametres:
       VOID                                     {
                                                    $$ = makeNode(Parametres);
                                                    Node *child = makeNode(Type);
                                                    child->name = strdup($1);
                                                    addChild($$, child);
                                                }
    |  ListTypVar                               {
                                                    $$ = makeNode(Parametres);
                                                    addChild($$, $1);
                                                }
    ;
ListTypVar:
       ListTypVar ',' TYPE IDENT                {
                                                    Node *child = makeNode(Type);
                                                    Node *child2 = makeNode(Ident);
                                                    child->name = strdup($3);
                                                    child2->name = strdup($4);
                                                    addSibling($1, child);
                                                    addChild(child, child2);
                                                }
    |  TYPE IDENT                               {
                                                    $$ = makeNode(Type);
                                                    Node *child = makeNode(Ident);
                                                    $$->name = strdup($1);
                                                    child->name = strdup($2);
                                                    addChild($$, child);
                                                }
    ;
Corps: '{' DeclarVarLoc SuiteInstr '}'          {
                                                    $$ = makeNode(Corps);
                                                    if (varLoc_flag && suiteInstr_flag){
                                                        addChild($$, $2);
                                                        addSibling($2, $3);
                                                    } else if (!varLoc_flag && suiteInstr_flag){
                                                        deleteTree($2);
                                                        addChild($$, $3);
                                                    } else if (varLoc_flag && !suiteInstr_flag){
                                                        deleteTree($3);
                                                        addChild($$, $2);
                                                    } else {
                                                        deleteTree($2);
                                                        deleteTree($3);
                                                        deleteTree($$);
                                                        $$ = NULL;
                                                    }
                                                }
    ;
DeclarVarLoc:
       DeclarVarLoc TYPE DeclarateursLoc ';'    {
                                                    if (!varLoc_flag)
                                                        varLoc_flag = 1;
                                                    Node *child;
                                                    child = makeNode(Type);
                                                    child->name = strdup($2);
                                                    addChild($$, child);
                                                    addChild(child, $3);
                                                }
    |                                           {
                                                    $$ = makeNode(DeclarVarLoc);
                                                }
    ;
DeclarateursLoc:
       DeclarateursLoc ',' IDENT Affectation    {
                                                    $$ = $1;
                                                    if ($4){
                                                        Node *tmp = $4->firstChild;
                                                        Node *ident = makeNode(Ident);
                                                        ident->name = strdup($3);
                                                        addSibling(ident, tmp);
                                                        $4->firstChild = ident;
                                                        addSibling($1, $4);
                                                    } else {
                                                        Node *sibling = makeNode(Ident);
                                                        sibling->name = strdup($3);
                                                        addSibling($1, sibling);
                                                        addChild(sibling, $4);
                                                    }
                                                    
                                                }
    |  IDENT Affectation                        {
                                                    if ($2){
                                                        $$ = $2;
                                                        Node *tmp = $$->firstChild;
                                                        Node *ident = makeNode(Ident);
                                                        ident->name = strdup($1);
                                                        addSibling(ident, tmp);
                                                        $$->firstChild = ident;
                                                    } else {
                                                        $$ = makeNode(Ident);
                                                        $$->name = strdup($1);
                                                        addChild($$, $2);
                                                    }
                                                }
    ;
Affectation:
       '=' Exp                                  {
                                                    $$ = makeNode(Assign);
                                                    $$->name = strdup("=");
                                                    addChild($$, $2);
                                                }
    |                                           {
                                                    $$ = NULL;
                                                }
    ;
    
SuiteInstr:
       SuiteInstr Instr                         {
                                                    if (!suiteInstr_flag)
                                                        suiteInstr_flag = 1;
                                                    $$ = $1;
                                                    addChild($$, $2);
                                                }   
    |                                           {
                                                    $$ = makeNode(SuiteInstr);
                                                }
    ;
Instr:
       LValue '=' Exp ';'                       {   
                                                    $$ = makeNode(Assign);
                                                    $$->name = strdup("=");
                                                    addChild($$, $1);
                                                    addChild($$, $3);
                                                }
    |  IF '(' Exp ')' Instr %prec THEN          {
                                                    $$ = makeNode(_if_);
                                                    addChild($$, $3);
                                                    addChild($$, $5);
                                                }
    |  IF '(' Exp ')' Instr ELSE Instr          {
                                                    $$ = makeNode(_if_);
                                                    addChild($$, $3);
                                                    addChild($$, $5);
                                                    Node *else__ = makeNode(_else_);
                                                    addSibling($$, else__);
                                                    addChild(else__, $7);
                                                }
    |  WHILE '(' Exp ')' Instr                  {
                                                    $$ = makeNode(_while_);
                                                    addChild($$, $3);
                                                    addChild($$, $5);
                                                }
    |  IDENT '(' Arguments  ')' ';'             {
                                                    $$ = makeNode(Ident);
                                                    $$->name = strdup($1);
                                                    addChild($$, $3);
                                                }
    |  RETURN Exp ';'                           {
                                                    $$ = makeNode(_return_);
                                                    addChild($$, $2);
                                                }
    |  RETURN ';'                               {
                                                    $$ = makeNode(_return_);
                                                }
    |  '{' SuiteInstr '}'                       {
                                                    $$ = $2;
                                                }
    |  ';'                                      {
                                                    $$ = NULL;
                                                }
    ;
Exp :  Exp OR TB                                {
                                                    $$ = makeNode(or);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
                                                }
    |  TB                                       {
                                                    $$ = $1;
                                                }
    ;
TB  :  TB AND FB                                {
                                                    $$ = makeNode(and);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
                                                }
    |  FB                                       {
                                                    $$ = $1;
                                                }
    ;
FB  :  FB EQ M                                  {
                                                    $$ = makeNode(Eq);
                                                    $$->name = strdup($2);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
                                                }
    |  M                                        {
                                                    $$ = $1;
                                                }
    ;
M   :  M ORDER E                                {
                                                    $$ = makeNode(Order);
                                                    $$->name = strdup($2);
                                                    addChild($$, $1);
                                                    addChild($$, $3);                                                  
                                                }

    |  E                                        {
                                                    $$ = $1;
                                                }
    ;
E   :  E ADDSUB T                               {
                                                    $$ = makeNode(Addsub);
                                                    $$->name = strdup($2);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
                                                }
    |  T                                        {
                                                    $$ = $1;
                                                }
    ;    
T   :  T DIVSTAR F {
                                                    $$ = makeNode(Divstar); 
                                                    $$->name = strdup($2);
                                                    addChild($$, $1); 
                                                    addChild($$, $3); 
                                                }
    |  F                                        {
                                                    $$ = $1;
                                                }
    ;
F   :  ADDSUB F                                 {
                                                    $$ = makeNode(UnaryAddsub);
                                                    $$->name = strdup($1);
                                                    addChild($$, $2);
                                                }
    |  '!' F                                    {
                                                    $$ = makeNode(not);
                                                    addChild($$, $2);
                                                }
    |  '(' Exp ')'                              {
                                                    $$ = $2;
                                                }
    |  NUM                                      {
                                                    $$ = makeNode(Num);
                                                    $$->isnum = 1;
                                                    $$->val = $1;
                                                }
    |  CHARACTER                                {
                                                    $$ = makeNode(Character);
                                                    $$->name = strdup($1); 
                                                }
    |  LValue                                   { 
                                                    $$ = $1;
                                                }
    |  IDENT '(' Arguments  ')'                 {    
                                                    $$ = makeNode(Ident);
                                                    $$->name = strdup($1);
                                                    addChild($$, $3);
                                                    
                                                }
    ;
LValue:
       IDENT                                    {
                                                    $$ = makeNode(Ident);
                                                    $$->name = strdup($1);
                                                }
    ;
Arguments:
       ListExp                                  {
                                                    $$ = makeNode(Arguments);
                                                    addChild($$, $1);
                                                }
    |                                           {
                                                    $$ = makeNode(Arguments);
                                                    Node * Child = makeNode(Type);
                                                    Child->name = strdup("void");
                                                    addChild($$, Child);
                                                }
    ;
ListExp:
       ListExp ',' Exp                          { 
                                                    addSibling($1, $3);
                                                }                   
    |  Exp                                      { 
                                                    $$ = $1; 
                                                }
    ;
%%

int yyerror(char *msg){
    fprintf(stderr, "Parse error in line %d, near column %d\n%s\n", 
            lineno, errorinline, msg);
    return 0;
}

int main(int argc, char *argv[]){
    int retval;
    if (read_option(argc, argv) == 1){
        fprintf(stderr, "option do not exists\n");
        return 2;
    }
    if (help_flag){
        print_synopsis();
        return 2;
    }
    if (argc > 1 && !last_is_option(argc, argv)){
        freopen(argv[argc - 1], "r", stdin);
    }
    retval = yyparse();
    if (err_flag) {
        return 2;
    }
    return retval;
}
