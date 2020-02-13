
#pragma once

/* tensor */
typedef struct tensor {
  int *arr;
  int *dims;
  int ndims;
} tensor;
void tPrint(tensor *t);

/* symbol table */
typedef struct symbol { /* a variable name */
  char *name;
  tensor *tnsr;
} symbol;

/* simple symtab of fixed size */
#define NHASH 9997
symbol symtab[NHASH];

symbol *lookup(char *);

/* list of nums */
typedef struct numlist {
  int num;
  struct numlist *next;
} numlist;

numlist *newnumlist(int dim, numlist *next);
void numlistfree(numlist *dl);

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
  numlist *dl;
} symref;

typedef struct symasgn {
  int nodetype; /* type = */
  symbol *s;
  node *v; /* value */
} symasgn;

/* build an AST */
node *newast(int nodetype, node *l, node *r);
node *newref(symbol *s, numlist *dl);
node *newasgn(symbol *s, node *v);

/* evaluate an AST */
tensor *eval(node *);

/* delete and free an AST */
void treefree(node *);

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

extern int debug;
void dumpast(node *a, int level);
