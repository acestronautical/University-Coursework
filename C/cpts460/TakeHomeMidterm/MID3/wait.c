extern int tswitch();
extern int int_off();
extern int int_on();

int ksleep(int event) {
  int sr = int_off();
  printf("proc %d going to sleep on event=%x\n", running->pid, event);
  running->event = event;
  running->status = SLEEP;
  enqueue(&sleepList, running);
  tswitch();
  int_on(sr);
}

int kwakeup(int event) {
  PROC *temp = 0, *p;
  int sr = int_off();
  printf("\nwakeup with event=%x\n", event);

  while (p = dequeue(&sleepList)) {
    if (p->event == event) {
      printf("waking up p%d\n", p->pid);
      p->status = READY;
      enqueue(&readyQueue, p);
    } else {
      enqueue(&temp, p);
    }
  }
  sleepList = temp;
  int_on(sr);
}

int kexit(int exitCode) {
  int i;
  PROC *p;

  running->exitCode = exitCode;
  running->status = ZOMBIE;
  running->child = 0;

  kwakeup((int)running->parent);
  tswitch();
}
