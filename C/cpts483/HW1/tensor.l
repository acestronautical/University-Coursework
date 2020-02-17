%option noyywrap nodefault yylineno
%{
# include "tensor.h"
# include "tensor.tab.h"
%}

%%
 /* All the single ladies */
"+" |
"-" |
"*" |
"/" |
"=" |
"," |
";" |
"[" |
"]" |
"{" |
"}" |
"(" |
")"     { return yytext[0]; }

 /* Keywooords */
"Tensor"    { return TENSOR; }

 /* Namumbers */
[A-Z]+  { yylval.s = lookup(yytext); return NAME; }
[0-9]+ { yylval.d = atoi(yytext); return NUMBER; }

 /* Trash */
"//".*  
[ \t\n]   /* ignore white space */ 
\\\n    /* ignore line continuation */
<<EOF>>                    { yyterminate(); }
. { yyerror((char*)"dont know what to do %c\n", *yytext); }

%%
