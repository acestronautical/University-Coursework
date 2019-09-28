#include "type.h"
// tqe stuff

typedef struct tq {
  struct tq *next;   // next element pointer
  int time;          // requested time
  struct PROC *proc; // pointer to PROC
  int (*action)();   // 0|1|handler function pointer
} TQE;
TQE *tq, tqe[NPROC];

// itimer(t): sets an interval timer of t seconds. Send a SIGALRM (14) signal to
// the process when the interval timer expires.

int itimer(TQE *t) {
  // (1). Fill in TQE[pid] information, e.g. proc pointer, action.
  // (2). lock();
  // // mask out interrupts
  // (3). traverse timer queue to compute the position to insert TQE;
  // (4). insert the TQE and update the time of next TQE;
  // (5). unlock();
  // unmask interrupts
}