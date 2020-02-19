
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
  intlist *l;
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
%type <l> initlist dimlist numlist
%type <d> dim
%start calclist

%%

exp: exp '+' exp          { $$ = newast('+', $1,$3); }
   | exp '*' exp          { $$ = newast('*', $1,$3); }
   | '(' exp ')'          { $$ = $2; }
   | TENSOR NAME dimlist  { $$ = newdec($2, $3); }
   | NAME '=' initlist    { $$ = newinit($1, $3); }
   | NAME '=' exp         { $$ = newasgn($1, $3); }
   | NAME                 { $$ = newref($1); }
;

initlist: '{' numlist '}' { $$ = $2; }
;
numlist: NUMBER           { $$ = newintlist($1, NULL); }
        | NUMBER ',' numlist   {$$ = newintlist($1, $3); }
;

dim: '[' NUMBER ']'       { $$ = $2; }
;
dimlist:  dim             { $$ = newintlist($1, NULL); }
        | dim dimlist     { $$ = newintlist($1, $2); }
;

calclist: /* nothing */
  | calclist exp ';' { 
          eval($2);
          treefree($2); }
  | calclist error EOL { yyerrok; printf("> "); }
 ;
%%
