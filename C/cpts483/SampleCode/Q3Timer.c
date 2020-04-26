#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  long begin = clock();

  /* here, do your time-consuming job */

  long end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  return 0;
}

long timer() { return clock(); }