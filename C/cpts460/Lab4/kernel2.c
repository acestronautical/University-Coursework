
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

  while (p = dequeue(&sleepList)) {
    if (p->event == event) {
      p->status = READY;
      enqueue(&readyQueue, p);
    } else {
      enqueue(&temp, p);
    }
  }
  sleepList = temp;
  int_on(sr);
}

int kexit(int exitValue) {
  printf("proc %d in kexit(), value=%d\n", running->pid, exitValue);
  if (running->pid == 1)
    return printf("kexit P1 failed: permission denied\n");
  running->exitCode = exitValue;
  running->status = ZOMBIE;
  for (int i = 0; i < NPROC; i++) {
    if (proc[i].ppid == running->pid) {
      proc[i].parent = &proc[1];
      proc[i].ppid = 1;
    }
  }
  tswitch();
}

int kwait(int *status) {
  PROC *p = 0;
  while (!p) {
    for (int i = 0; i < NPROC; i++) {
      if (proc[i].ppid == running->pid && proc[i].status == ZOMBIE) {
        p = &proc[i];
        printf("found zombie P%d", p->pid);
      }
    }
    if (p) {
      *status = p->exitCode;
      enqueue(&freeList, p);
      p->parent = 0;
      p->ppid = 0;
      p->status = FREE;
      return p->pid;
    } else
      ksleep((int)running);
  }
}
