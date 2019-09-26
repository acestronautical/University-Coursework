#include "type.h"

void enqueue(PROC **queue, PROC *p)
{
  PROC *q  = *queue;
  if (q==0 || p->priority > q->priority){
    *queue = p;
    p->next = q;
    return;
  }
  while (q->next && p->priority <= q->next->priority){
    q = q->next;
  }
  p->next = q->next;
  q->next = p;
}

PROC *dequeue(PROC **queue)
{
  PROC *p = *queue;
  if (p)
    *queue = p->next;
  return p;
}

void printList(char *name, PROC *list)
{
  printf("%s=", name);
  PROC *p = list;
  while(p){
    printf("[%d%d]->", p->pid, p->priority);
    p = p->next;
  }
  printf("NULL\n");
}

void printTree(char *name, PROC *p) {
  PROC *children[16];
  int i = 0;
  printf("%s = ", name);
  while (p) {
    printf("[%d %d]->", p->pid, p->priority);
    if (p->child)
      children[i++] = p->child;
    p = p->sibling;
  }
  children[i++] = 0;
  printf("\n");
  for (i = 0; children[i]; i++)
    printTree("             ", children[i]);
}