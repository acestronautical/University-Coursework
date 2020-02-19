
#pragma once

/* tensor */
typedef struct tensor {
  int *arr;
  int *dims;
  int ndims;
} tensor;

/* symbol table */
typedef struct symbol { /* a variable name */
  char *name;
  tensor tnsr;
} symbol;

/* simple symtab of fixed size */
#define NHASH 9997
symbol symtab[NHASH];

void tensorprint(symbol *);
symbol *lookup(char *);

/* list of nums */
typedef struct intlist {
  int* arr;
  int len;
  int cap;
} intlist;

intlist *newintlist(int num, intlist *l);
void intlistfree(intlist *l);

/* node types
 *  + *
 *  N symbol ref
 *  = assignment
 */

/* nodes in the Abstract Syntax Tree */
/* all have common initial nodetype */

typedef struct node {
  int type;
  struct node *l;
  struct node *r;
} node;

typedef struct symref {
  int nodetype; /* type R */
  symbol *s;
  intlist *l;
} symref;

typedef struct symasgn {
  int nodetype; /* type = */
  symbol *s;
  node *v; /* value */
} symasgn;

/* build an AST */
node *newast(int nodetype, node *l, node *r);
node *newdec(symbol *s, intlist *l);
node *newasgn(symbol *s, node *v);
node *newinit(symbol *s, intlist *l);
node *newref(symbol *s);

/* evaluate an AST */
symbol *eval(node *);

/* delete and free an AST */
void treefree(node *);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

extern int debug;
void dumpast(node *a, int level);
