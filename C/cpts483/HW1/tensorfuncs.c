
#include "tensor.h"
#include "tensor.tab.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* symbol table */
/* hash a symbol */
static unsigned symhash(char *sym) {
  unsigned int hash = 0;
  unsigned c;

  while (c = *sym++)
    hash = hash * 9 ^ c;

  return hash;
}

symbol *lookup(char *sym) {
  symbol *sp = &symtab[symhash(sym) % NHASH];
  int scount = NHASH; /* how many have we looked at */

  while (--scount >= 0) {
    if (sp->name && !strcmp(sp->name, sym)) {
      return sp;
    }

    if (!sp->name) { /* new entry */
      sp->name = strdup(sym);
      sp->tnsr = (tensor *)malloc(sizeof(tensor));
      sp->tnsr->arr = NULL;
      sp->tnsr->dims = NULL;
      sp->tnsr->ndims = 0;
      return sp;
    }

    if (++sp >= symtab + NHASH)
      sp = symtab; /* try the next entry */
  }
  yyerror("symbol table overflow\n");
  abort(); /* tried them all, table is full */
}

node *newast(int nodetype, node *l, node *r) {
  node *a = malloc(sizeof(node));

  if (!a) {
    yyerror("out of space");
    exit(0);
  }
  a->type = nodetype;
  a->l = l;
  a->r = r;
  return a;
}

node *newref(symbol *s, numlist *dl) {
  symref *a = malloc(sizeof(symref));

  if (!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'R';
  a->s = s;
  a->dl = dl;
  return (node *)a;
}

node *newinit(symbol *s, numlist *dl) {
  symref *a = malloc(sizeof(symref));

  if (!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'I';
  a->s = s;
  a->dl = dl;
  return (node *)a;
}

node *newasgn(symbol *s, node *v) {
  symasgn *a = malloc(sizeof(symasgn));

  if (!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = '=';
  a->s = s;
  a->v = v;
  return (node *)a;
}

numlist *newnumlist(int dim, numlist *next) {
  numlist *dl = malloc(sizeof(numlist));

  if (!dl) {
    yyerror("out of space");
    exit(0);
  }
  dl->num = dim;
  dl->next = next;
  return dl;
}

void numlistfree(numlist *dl) {
  numlist *ndl;

  while (dl) {
    ndl = dl->next;
    free(dl);
    dl = ndl;
  }
}

void tPrint(tensor *t) {
  if (!t | !t->arr | !t->dims | t->ndims == 0) {
    printf("noval\n");
    return;
  }
  int sz = 1;
  for (int i = 0; i < t->ndims; i++) {
    sz *= t->dims[i];
  }
  for (int i = 0; i < sz; i++) {
    printf("%d, ", t->arr[i]);
  }
}

tensor tAdd(tensor *t1, tensor *t2) {
  tensor t;
  int sz = 1;
  if (t1->ndims != t2->ndims)
    exit(1);
  t.ndims = t1->ndims;
  t.dims = (int *)malloc(sizeof(int) * t.ndims);
  for (int i = 0; i < t1->ndims; i++) {
    if (t1->dims[i] != t2->dims[i])
      exit(1);
    sz *= t1->dims[i];
    t.dims[i] = t1->dims[i];
  }
  t.arr = (int *)malloc(sizeof(int) * sz);
  for (int i = 0; i < sz; i++) {
    t.arr[i] = t1->arr[i] + t2->arr[i];
  }
  return t;
}

tensor tMul(tensor *t1, tensor *t2) {
  tensor t;
  if (t1->ndims > 2 || t2->ndims > 2)
    exit(1);
  t.ndims = t1->ndims;
  t.dims = (int *)malloc(sizeof(int) * t.ndims);

  t.dims[0] = t1->dims[1];
  t.dims[1] = t2->dims[0];

  for (int i = 0; i < t1->dims[0]; i++) {
    for (int j = 0; j < t1->dims[1]; j++) {
      int sum = 0;
      for (int k = 0; k < t1->dims[0]; k++)
        sum = sum + (*(t1->arr + i * t1->dims[0] + k) *
                     *(t2->arr + k * t2->dims[0] + j));

      *(t.arr + i * t.dims[0] + j) = sum;
    }
  }
  return t;
}

tensor *eval(node *a) {
  tensor tens, *t = &tens;

  if (!a) {
    yyerror("internal error, null eval");
    return NULL;
  }

  switch (a->type) {
    /* name reference */
  case 'R':
    t = ((symref *)a)->s->tnsr;
    break;

    /* name initialization */
  case 'I':
    t = ((symref *)a)->s->tnsr;
    break;

    /* assignment */
  case '=':
    t = ((symasgn *)a)->s->tnsr = eval(((symasgn *)a)->v); // todo
    break;

    /* expressions */
  case '+':
    *t = tAdd(eval(a->l), eval(a->r));
    break;
  case '*':
    *t = tMul(eval(a->l), eval(a->r));
    break;
  case 'L':
    eval(a->l);
    t = eval(a->r);
    break;

  default:
    printf("internal error: bad node %c\n", a->type);
  }
  return t;
}

void treefree(node *a) {
  switch (a->type) {

    /* two subtrees */
  case '+':
  case '*':
    treefree(a->r);

    /* no subtree */
  case 'R':
    break;

  case '=':
    free(((symasgn *)a)->v);
    break;

  default:
    printf("internal error: free bad node %c\n", a->type);
  }

  free(a); /* always free the node itself */
}

void yyerror(char *s, ...) {
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

#ifdef YYDEBUG
yydebug = 1;
#endif
int main() {
  printf("> ");
  return yyparse();
}

/* debugging: dump out an AST */
int debug = 0;
void dumpast(node *a, int level) {

  printf("%*s", 2 * level, ""); /* indent to this level */
  level++;

  if (!a) {
    printf("NULL\n");
    return;
  }

  switch (a->type) {
    /* name reference */
  case 'R':
    printf("ref %s\n", ((symref *)a)->s->name);
    break;

    /* assignment */
  case '=':
    printf("= %s\n", ((symref *)a)->s->name);
    dumpast(((symasgn *)a)->v, level);
    return;

    /* expressions */
  case '+':
  case '*':
    printf("binop %c\n", a->type);
    dumpast(a->l, level);
    dumpast(a->r, level);
    return;

  default:
    printf("bad %c\n", a->type);
    return;
  }
}
