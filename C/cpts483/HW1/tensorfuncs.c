
#include "tensor.h"
#include "tensor.tab.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  node *a = (node *)malloc(sizeof(node));
  *a = (node){.type = nodetype, .l = l, .r = r};
  return a;
}

node *newref(symbol *s) {
  struct symref *a = malloc(sizeof(struct symref));
  a->nodetype = 'R';
  a->s = lookup(s->name);
  return (node *)a;
}

node *newdec(symbol *s, intlist *l) {
  symref *sr = (symref *)malloc(sizeof(symref));
  *sr = (symref){.nodetype = 'D', .s = s, .l = l};
  return (node *)sr;
}

node *newinit(symbol *s, intlist *l) {
  symref *sr = (symref *)malloc(sizeof(symref));
  *sr = (symref){.nodetype = 'I', .s = s, .l = l};
  return (node *)sr;
}

node *newasgn(symbol *s, node *v) {
  symasgn *sa = (symasgn *)malloc(sizeof(symasgn));
  *sa = (symasgn){.nodetype = '=', .s = s, .v = v};
  return (node *)sa;
}

intlist *appendint(intlist *l, int num) {
  if (l->cap == l->len) {
    l->cap = l->cap * 2;
    l->arr = (int *)realloc(l->arr, l->cap * sizeof(int));
  }
  l->arr[l->len++] = num;
  return l;
}

intlist *newintlist(int num, intlist *l) {
  intlist *list = l;
  if (!list) {
    list = (intlist *)malloc(sizeof(intlist));
    list->arr = (int *)malloc(sizeof(int) * 2);
    list->cap = 2;
    list->len = 0;
  }
  appendint(list, num);
  return list;
}

void intlistfree(intlist *l) {
  free(l->arr);
  free(l);
}

void tPrint(tensor *t) {
  if (!t | !t->arr | !t->dims | t->ndims == 0) {
    printf("//[]\n");
    return;
  }
  int sz = 1;
  for (int i = 0; i < t->ndims; i++) {
    sz *= t->dims[i];
  }
  printf("\n//[] = \n//");
  for (int i = 0; i < sz; i++) {
    printf("%d, ", t->arr[i]);
    if ((i + 1) % t->dims[0] == 0)
      printf("\n//");
  }
  printf("\n");
}

tensor tDec(tensor *t, intlist *l) {
  t->ndims = l->len;
  t->dims = (int *)malloc(sizeof(int) * t->ndims);
  int sz = 1;
  for (int i = 0; i < t->ndims; i++) {
    t->dims[i] = l->arr[i];
    sz *= l->arr[i];
  }
  t->arr = (int *)malloc(sizeof(int) * sz);
};

tensor tInit(tensor *t, intlist *l) {
  for (int i = 0; i < l->len; i++)
    t->arr[i] = l->arr[i];
};

tensor *tAdd(tensor *t1, tensor *t2) {
  tensor *t = (tensor *)malloc(sizeof(tensor));
  int sz = 1;
  if (t1->ndims != t2->ndims)
    exit(1);
  t->ndims = t1->ndims;
  t->dims = (int *)malloc(sizeof(int) * t->ndims);
  for (int i = 0; i < t1->ndims; i++) {
    if (t1->dims[i] != t2->dims[i])
      exit(1);
    sz *= t1->dims[i];
    t->dims[i] = t1->dims[i];
  }
  t->arr = (int *)malloc(sizeof(int) * sz);
  for (int i = 0; i < sz; i++) {
    t->arr[i] = t1->arr[i] + t2->arr[i];
  }
  return t;
}

tensor *tMul(tensor *t1, tensor *t2) {
  tensor *t = (tensor *)malloc(sizeof(tensor));
  if (t1->ndims > 2 || t2->ndims > 2){
    printf("can't multiply these dimensions\n");
    exit(1);
  }
  t->ndims = t1->ndims;
  t->dims = (int *)malloc(sizeof(int) * t->ndims);
  t->dims[0] = t1->dims[1];
  t->dims[1] = t2->dims[0];

  int sz =1;
 for (int i = 0; i < t->ndims; i++) 
    sz *= t->dims[i];

  t->arr = (int *)malloc(sizeof(int) * sz);

  for (int i = 0; i < t1->dims[0]; i++) {
    for (int j = 0; j < t1->dims[1]; j++) {
      int sum = 0;
      for (int k = 0; k < t1->dims[0]; k++)
        sum = sum + (*(t1->arr + i * t1->dims[0] + k) *
                     *(t2->arr + k * t2->dims[0] + j));

      *(t->arr + i * t->dims[0] + j) = sum;
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
    /* name declaration */
  case 'D':
    tDec(((symref *)a)->s->tnsr, ((symref *)a)->l);
    t = ((symref *)a)->s->tnsr;
    break;

    /* name initialization */
  case 'I':
    tInit(((symref *)a)->s->tnsr, ((symref *)a)->l);
    t = ((symref *)a)->s->tnsr;
    break;

    /* name reference */
  case 'R':
    t = ((struct symref *)a)->s->tnsr;
    break;

    /* assignment */
  case '=':
    t = ((symasgn *)a)->s->tnsr = eval(((symasgn *)a)->v);
    break;

    /* expressions */
  case '+':
    t = tAdd(eval(a->l), eval(a->r));
    break;
  case '*':
    t = tMul(eval(a->l), eval(a->r));
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
    treefree(a->l);

    /* no subtree */
  case 'I':
    free(((symref *)a)->l);
  case 'D':
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
int yydebug = 1;
#endif
int main() {
  printf("> ");
  return yyparse();
}
