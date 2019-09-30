#include "type.h"
#include "wait.c"

int body();

int stringcpy(char *dest, char *src) {
  while (*src) {
    *dest++ = *src++;
  }
  *dest = 0;
}

int init() {
  int i, j;
  PROC *p;
  TQE *t;
  kprintf("kernel_init()\n");
  for (i = 0; i < NPROC; i++) {
    // init procs
    p = &proc[i];
    p->pid = i;
    p->status = READY;
    p->next = p + 1;
  }

  proc[NPROC - 1].next = 0; // circular proc list
  freeList = &proc[0];
  readyQueue = 0;
  sleepList = 0;
  printList("freeList", freeList);

  // creat P0 as initial running process
  p = (PROC *)dequeue(&freeList);
  p->priority = 0;
  p->ppid = 0;
  p->parent = p;
  p->child = 0;
  p->sibling = 0;
  running = p;

  kprintf("running = %d\n", running->pid);
}

char *status[] = {"FREE", "READY", "SLEEP", "BLOCK", "ZOMBIE"};

PROC *kfork(int func, int priority) {
  int i;
  PROC *p = (PROC *)dequeue(&freeList);
  if (p == 0) {
    printf("no more PROC, kfork failed\n");
    return 0;
  }
  p->status = READY;
  p->priority = priority;
  p->ppid = running->pid;

  p->parent = running;
  p->child = 0;
  p->sibling = 0;

  // set kstack to resume to body
  // stack = r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r14
  //         1  2  3  4  5  6  7  8  9  10 11  12  13  14
  for (i = 1; i < 15; i++)
    p->kstack[SSIZE - i] = 0;
  p->kstack[SSIZE - 1] = (int)func; // in dec reg=address ORDER !!!
  p->ksp = &(p->kstack[SSIZE - 14]);
  enqueue(&readyQueue, p);
  printf("proc %d kforked a child %d\n", running->pid, p->pid);
  return p;
}

int scheduler() {
  kprintf("proc %d in scheduler ", running->pid);
  if (running->status == READY)
    enqueue(&readyQueue, running);
  running = (PROC *)dequeue(&readyQueue);
  kprintf("next running = %d\n", running->pid);
}

int body() {

  char tstring[64];
  int pid, tval;

  while (1) {
    pid = running->pid;
    kprintf("\nproc %d resume to body()\n", running->pid);
    printList("readyQueue", readyQueue);
    kprintf("proc %d running : ", pid);
    tval = 0;
    while (tval < 1 || tval > 99) {
      printf("\nenter amount of time to sleep for: ");
      kgets(tstring);
      tval = atoi(tstring);
    }
    insert_TQE(tval);
    ksleep(pid);
    tswitch();
  }
}
