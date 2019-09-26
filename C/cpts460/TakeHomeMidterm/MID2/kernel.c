#include "type.h"

int init() {
  int i, j;
  PROC *p;
  kprintf("kernel_init()\n");
  for (i = 0; i < NPROC; i++) {
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

// PROC OPERATIONS //

char *status[] = {"FREE", "READY", "SLEEP", "BLOCK", "ZOMBIE"};

int ksleep(int event) {
  int sr = int_off();

  printf("proc %d going to sleep on event=%x\n", running->pid, event);
  running->event = event;
  running->status = SLEEP;
  enqueue(&sleepList, running);
  printList("sleepList", sleepList);
  tswitch();

  int_on(sr);
}

int kwakeup(int event) {
  int sr = int_off();

  PROC *temp, *p;
  temp = 0;
  printList("sleepList", sleepList);
  p = dequeue(&sleepList);
  while (p) {
    if (p->event == event) {
      printf("wakeup %d\n", p->pid);
      p->status = READY;
      enqueue(&readyQueue, p);
    } else {
      enqueue(&temp, p);
    }
    p = dequeue(&sleepList);
  }
  sleepList = temp;
  printList("sleepList", sleepList);

  int_on(sr);
}

void orphan(PROC *waif) {
  if (!waif)
    return;
  PROC *orphanage = &proc[1];
  printf("giving away orphaned P%d to P1\n", waif->pid);
  waif->ppid = 1;

  if (!orphanage->child)
    orphanage->child = waif;
  else {
    orphanage = orphanage->child;
    while (orphanage->sibling)
      orphanage = orphanage->sibling;
    orphanage->sibling = waif;
  }

  orphan(waif->sibling);
  waif->sibling = 0;
  orphan(waif->child);
  waif->child = 0;
}

void bury(PROC *victim) {
  PROC *bereaved = victim->parent;
  if (bereaved->child == victim)
    bereaved->child = victim->sibling;
  else {
    PROC *younger = bereaved->child, *older = bereaved->child;
    while (older != victim) {
      younger = older;
      older = older->sibling;
    }
    younger->sibling = older->sibling;
  }
  victim->sibling = 0;
  victim->child = 0;
  victim->parent = 0;
  victim->status = FREE;
}

int kexit(int exitCode) {
  if (running->pid == 1)
    return printf("P1 cannot die\n");

  orphan(running->child);
  running->child = 0;
  running->exitCode = exitCode;
  running->status = ZOMBIE;
  tswitch();
}

int kwait(int *status) {
  printf("proc %d waits for a ZOMBIE child\n", running->pid);
  if (!running->child) {
    printf("wait error: no child\n");
    return -1;
  }

  while (1) {
    PROC *zombie = running->child;
    while (!(zombie && zombie->status == ZOMBIE))
      zombie = zombie->sibling;

    if (zombie) {
      int zpid = zombie->pid;
      printf("P%d buried ZOMBIE child P%d with exitCode %d\n", running->pid,
             zombie->pid, zombie->exitCode);
      bury(zombie);
      enqueue(&freeList, zombie);
      return zpid;
    }
    printf("P%d wait for ZOMBIE child\n", running->pid);
    ksleep(running->pid);
  }
}

PROC *kfork(int func, int priority) {
  int i;
  PROC *p = (PROC *)dequeue(&freeList);
  if (p == 0) {
    printf("no more system PROC's, kfork failed\n");
    return 0;
  }
  p->status = READY;
  p->priority = priority;
  p->ppid = running->pid;

  p->parent = running;
  p->child = 0;
  p->sibling = 0;

  // insert into tree
  PROC *cur;
  if (!running->child)
    running->child = p;
  else {
    cur = running->child;
    while (cur->sibling)
      cur = cur->sibling;
    cur->sibling = p;
  }

  // set kstack to resume to body
  // stack = r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r14
  //         1  2  3  4  5  6  7  8  9  10 11  12  13  14
  for (i = 1; i < 15; i++)
    p->kstack[SSIZE - i] = 0;
  p->kstack[SSIZE - 1] = (int)func; // in dec reg=address ORDER !!!
  p->ksp = &(p->kstack[SSIZE - 14]);
  enqueue(&readyQueue, p);
  printf("FORK: p%d forked child p%d\n", running->pid, p->pid);
  printList("  readyQueue", readyQueue);
  return p;
}

int scheduler() {
  kprintf("proc %d in scheduler ", running->pid);
  if (running->status == READY)
    enqueue(&readyQueue, running);
  running = (PROC *)dequeue(&readyQueue);
  kprintf("next running = %d\n", running->pid);
}

int menu() {
  printf("------- menu --------\n");
  printf("switch fork exit wait\n");
  printf("---------------------\n");
}

int do_exit() {
  char s[16];
  int exitValue;
  if (running->pid == 1) {
    printf("P1 never dies\n");
    return -1;
  }
  printf("enter an exit value : ");
  kgets(s);
  exitValue = atoi(s);
  kexit(exitValue);
}

int do_wait() {
  int pid, status;
  printf("proc %d wait for a ZOMBIE child\n", running->pid);
  pid = kwait(&status);
  printf("proc %d wait for a ZOMBIE child %d ststus=%d\n", running->pid, pid,
         status);
}

int body() {
  char command[64];
  int pid, status;
  kprintf("proc %d resume to body()\n", running->pid);

  while (1) {

    pid = running->pid;
    if (pid == 0)
      color = BLUE;
    if (pid == 1)
      color = GREEN;
    if (pid == 2)
      color = CYAN;
    if (pid == 3)
      color = YELLOW;
    if (pid == 4)
      color = WHITE;
    if (pid == 5)
      color = GREEN;
    if (pid == 6)
      color = CYAN;
    if (pid == 7)
      color = YELLOW;
    if (pid == 8)
      color = WHITE;

    kprintf("RUNNING: p%d is running\n", running->pid);
    kprintf("  example    =[pid, priority]->\n");
    printList("  readyQueue ", readyQueue);
    printList("  freeList   ", freeList);

    menu();
    printf("$ ");
    kgets(command);

    if (strcmp(command, "switch") == 0)
      tswitch();
    if (strcmp(command, "fork") == 0)
      kfork((int)body, 1);
    if (strcmp(command, "exit") == 0)
      do_exit();
    if (strcmp(command, "wait") == 0)
      do_wait();
  }
}
