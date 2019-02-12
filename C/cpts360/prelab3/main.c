/*************** main() function ***************/
#include "mtx.h"

int main() {
  printf("Welcome to the MT Multitasking System\n");
  init();  // initialize system; create and run P0
  kfork(); // kfork P1 into readyQueue
  while (1) {
    printf("P0: switch process\n");
    while (!readyQueue)
      ;
    tswitch();
  }
}