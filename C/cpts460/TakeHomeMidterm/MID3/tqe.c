#include "type.h"
// tqe stuff

tqe_init() {
  for (int i = 0; i < NPROC; i++) {
    tqe[i].time = -1;
    tqe[i].pid = 0;
  }
}
// itimer(t): sets an interval timer of t seconds. Send a SIGALRM (14) signal to
// the process when the interval timer expires.

int insert_TQE(int tval) {

  // (1). Fill in TQE[pid] information, e.g. proc pointer, action.
  int sum = 0, rem = 0;
  int i = 0, j = 0;
  int sr = int_off();

  // calculate time
  for (; i < NPROC; i++) {
    if (((sum + tqe[i % NPROC].time) > tval) || (tqe[i % NPROC]).time < 0)
      break;
    sum += (tqe[i % NPROC]).time;
  }
  rem = tval - sum;

  // shift em over
  for (j = i + 1; j < NPROC - 1; j++)
    tqe[j % NPROC] = tqe[(j + 1) % NPROC];

  // insert new guy
  tqe[i % NPROC].time = rem;
  tqe[i % NPROC].pid = running->pid;

  // subtract from others
  for (j = i + 1; j < NPROC - 1; j++)
    tqe[j % NPROC].time -= rem;

  printf("entered pid %d to tqe with time %d \n", tqe[i % NPROC].pid,
         tqe[i % NPROC].pid);

  printf("head tq time %d, pid %d\n", tqe[curTQE].time, tqe[curTQE].pid);
  int_on(sr);
}