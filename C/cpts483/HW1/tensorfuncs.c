
#include "tensor.h"
#include "tensor.tab.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *TMPNAME = "tmp0000";
int AUTOID = 0;
char IDBUF[5];

static unsigned symhash(char *sym) {
  unsigned int hash = 0, c;
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
      sp->tnsr.arr = NULL;
      sp->tnsr.dims = NULL;
      sp->tnsr.ndims = 0;
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

void tensorprint(symbol *s) {
  tensor *t = &s->tnsr;
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

void tensordeclareprint(symbol *s, intlist *l) {
  printf("int %s", s->name);
  for (int i = 0; i < s->tnsr.ndims; i++)
    printf("[%d]", s->tnsr.dims[i]);
  printf(";\n");
}

symbol *tensordeclare(symbol *s, intlist *l) {
  tensor *t = &s->tnsr;
  t->ndims = l->len;
  t->dims = (int *)malloc(sizeof(int) * t->ndims);
  int sz = 1;
  for (int i = 0; i < t->ndims; i++) {
    t->dims[i] = l->arr[t->ndims - i - 1];
    sz *= l->arr[i];
  }
  t->arr = (int *)malloc(sizeof(int) * sz);
  return s;
}

void tensorinitprint(symbol *s, intlist *l){

};

symbol *tensorinit(symbol *s, intlist *l) {
  tensor *t = &s->tnsr;
  for (int i = 0; i < l->len; i++)
    t->arr[i] = l->arr[i];
  return s;
}

void tensoraddprint(symbol *s, symbol *s1, symbol *s2) {
  printf("int %s", s->name);
  for (int i = 0; i < s->tnsr.ndims; i++)
    printf("[%d]", s->tnsr.dims[i]);
  printf(";\n");

  int sz = 1;
  for (int i = 0; i < s->tnsr.ndims; i++) {
    sz *= s->tnsr.dims[i];
  }

  printf("for (int i = 0; i < %d; i++) {\n"
         "*(int *)%s[i] = *(int *)%s[i] + *(int *)%s[i];"
         "\n}\n",
         sz, s->name, s1->name, s2->name);
};

symbol *tensoradd(symbol *s1, symbol *s2) {
  symbol *s = (symbol *)malloc(sizeof(symbol));
  s->name = strdup(TMPNAME);
  s->name[4] = 0;
  sprintf(IDBUF, "%d", AUTOID++);
  strcat(s->name, IDBUF);
  tensor *t1 = &s1->tnsr, *t2 = &s2->tnsr, *t = &s->tnsr;
  int sz = 1;
  if (t1->ndims != t2->ndims) {
    printf("err: num dims not the same\n");
    exit(1);
  }
  t->ndims = t1->ndims;
  t->dims = (int *)malloc(sizeof(int) * t->ndims);
  for (int i = 0; i < t1->ndims; i++) {
    if (t1->dims[i] != t2->dims[i]) {
      printf("err: val of dims not the same\n %d != %d\n", t1->dims[i],
             t2->dims[i]);
      exit(1);
    }
    sz *= t1->dims[i];
    t->dims[i] = t1->dims[i];
  }

  t->arr = (int *)malloc(sizeof(int) * sz);
  for (int i = 0; i < sz; i++) {
    t->arr[i] = t1->arr[i] + t2->arr[i];
  }
  return s;
}

void tensormultiplyprint(symbol *s, symbol *s1, symbol *s2) {
  printf("int %s", s->name);
  for (int i = 0; i < s->tnsr.ndims; i++)
    printf("[%d]", s->tnsr.dims[i]);
  printf(";\n");

  tensor *t1 = &s1->tnsr, *t2 = &s2->tnsr, *t = &s->tnsr;

  printf("for (int i = 0; i < %d; i++) {\n"
         "   for (int j = 0; j < %d; j++) {\n"
         "     int sum = 0;\n"
         "     for (int k = 0; k < %d; k++)\n"
         "       sum = sum + *((int *)%s + i * %d + k) *\n"
         "                   *((int *)%s + k * %d + j);\n"
         "     *((int *)%s + i * %d + j) = sum;\n"
         "   }\n"
         " \n}\n",
         t1->dims[0], t1->dims[1], t1->dims[0], s1->name, t1->dims[0], s2->name,
         t2->dims[0], s->name, t->dims[0]);
}

symbol *tensormultiply(symbol *s1, symbol *s2) {
  symbol *s = (symbol *)malloc(sizeof(symbol));
  s->name = strdup(TMPNAME);
  s->name[4] = 0;
  sprintf(IDBUF, "%d", AUTOID++);
  strcat(s->name, IDBUF);
  tensor *t1 = &s1->tnsr, *t2 = &s2->tnsr, *t = &s->tnsr;
  if (t1->ndims > 2 || t2->ndims > 2) {
    printf("can't multiply these dimensions\n");
    exit(1);
  }
  t->ndims = t1->ndims;
  t->dims = (int *)malloc(sizeof(int) * t->ndims);
  t->dims[0] = t1->dims[0];
  if (t->ndims >= 2)
    t->dims[1] = t2->dims[1];

  int sz = 1;
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
  return s;
}

symbol *eval(node *a) {
  symbol *sym, *sym1, *sym2;
  switch (a->type) {
    /* name declaration */
  case 'D':
    tensordeclare(((symref *)a)->s, ((symref *)a)->l);
    tensordeclareprint(((symref *)a)->s, ((symref *)a)->l);
    sym = ((symref *)a)->s;
    break;
    /* name initialization */
  case 'I':
    tensorinitprint(((symref *)a)->s, ((symref *)a)->l);
    tensorinit(((symref *)a)->s, ((symref *)a)->l);
    sym = ((symref *)a)->s;
    break;
    /* name reference */
  case 'R':
    sym = ((struct symref *)a)->s;
    break;
    /* assignment */
  case '=':
    // deep copy
    sym = eval(((symasgn *)a)->v);
    sym1 = ((symasgn *)a)->s;
    memcpy(sym1->tnsr.arr, sym->tnsr.arr, sizeof(sym->tnsr.arr));
    memcpy(sym1->tnsr.dims, sym->tnsr.dims, sizeof(sym->tnsr.dims));
    sym1->tnsr.ndims = sym->tnsr.ndims;
    printf("memcpy(%s, %s, %d);\n", sym->name, sym1->name,
           (int)sizeof(sym->tnsr.arr));
    break;
    /* expressions */
  case '+':
    sym1 = eval(a->l);
    sym2 = eval(a->r);
    sym = tensoradd(sym1, sym2);
    tensoraddprint(sym, sym1, sym2);
    break;
  case '*':
    sym1 = eval(a->l);
    sym2 = eval(a->r);
    sym = tensormultiply(sym1, sym2);
    tensormultiplyprint(sym, sym1, sym2);
    break;
  default:
    printf("internal error: bad node %c\n", a->type);
  }
  return sym;
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
int yydebug = 0;
#endif
int main() {
  printf("void main(){\n");
  return yyparse();
  printf("\n}");
}
