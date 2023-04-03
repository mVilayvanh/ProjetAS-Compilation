
%{
    /* Lexique projet tpc */
%}

%option nounput
%option noinput
%option noyywrap
%x COMMENTAIRE

%{
#include "tree.h"
#include "tpcas.tab.h"
int lineno = 1;
int errorinline = 1;
%}

%%

int|char                    { errorinline+= yyleng; strcpy(yylval.type, yytext); return TYPE; }
void                        { errorinline+= yyleng; strcpy(yylval.type, yytext); return VOID; }
if                          { errorinline+= yyleng; return IF; }
else                        { errorinline+= yyleng; return ELSE; }
while                       { errorinline+= yyleng;return WHILE; }
return                      { errorinline+= yyleng;return RETURN; }


"||"                        { errorinline+= yyleng; strcpy(yylval.type,yytext); return OR;}
"&&"                        { errorinline+= yyleng; strcpy(yylval.type,yytext); return AND;}
[+-]                        { errorinline+= yyleng; strcpy(yylval.byte,yytext); return ADDSUB;}
[*/%]                       { errorinline+= yyleng; strcpy(yylval.type,yytext); return DIVSTAR;}
\<|<=|\>|>=                 { errorinline+= yyleng; strcpy(yylval.type,yytext); return ORDER; } 
==|!=                       { errorinline+= yyleng; strcpy(yylval.type,yytext); return EQ; }

[a-zA-Z_][a-zA-Z_0-9]*      { errorinline+= yyleng; strcpy(yylval.ident, yytext); return IDENT; }
[0-9]+                      { errorinline+= yyleng; yylval.num =atoi(yytext); return NUM; }
\'(.|\\t|\\n)\'             { errorinline+= yyleng; strcpy(yylval.byte,yytext);return CHARACTER; }

[;=\(\)\{\},!]              { errorinline += yyleng; return yytext[0]; }

"//".* ;
"/*"                        { errorinline += yyleng; BEGIN COMMENTAIRE; }
<COMMENTAIRE>\n             { errorinline = 0; lineno++; }
<COMMENTAIRE>(.|\r|\t) ;
<COMMENTAIRE>"*/"           { errorinline+= yyleng; BEGIN INITIAL; }
<<EOF>>                     { errorinline = 0; return 0; }

[ \t\r] ;
\n                          { errorinline = 0; lineno++; }
.                           { return 0; }

%%