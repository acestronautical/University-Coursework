
%{
#  include <stdio.h>
#  include <stdlib.h>
#  include "tensor.h"
int yylex();
%}

%union {
  node *a;
  int d;
  symbol *s;
  numlist *nl;
}

/* declare tokens */
%token <d> NUMBER
%token <s> NAME
%token EOL

%token TENSOR

%right '='
%left '+'
%left '*'

%type <a> exp 
%type <nl> initlist dimlist numlist
%type <d> dim
%start calclist

%%

exp: exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | '(' exp ')'          { $$ = $2; }
   | TENSOR NAME dimlist  { $$ = newref($2, $3); }
   | NAME '=' initlist    { $$ = newinit($1, $3); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
;

initlist: '{' numlist '}' { $$ = $2; }
;
numlist: NUMBER           { $$ = newnumlist($1, NULL); }
        | NUMBER ',' numlist   {$$ = newnumlist($1, $3); }
;

dim: '[' NUMBER ']'       { $$ = $2; }
;
dimlist:  dim             { $$ = newnumlist($1, NULL); }
        | dim dimlist     { $$ = newnumlist($1, $2); }
;

calclist: /* nothing */
  | calclist exp EOL { tPrint(eval($2)); }
  | calclist error EOL { yyerrok; printf("> "); }
 ;
%%
