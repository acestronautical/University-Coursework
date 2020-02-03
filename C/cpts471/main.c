#include "alignment.h"

/*
CptS 471/571 Assignment Cover Sheet

Assignment: Programming Project 1
Name: Cassidy, Ace

https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Typeof.html#Typeof


I certify that I have listed above all the sources that I consulted regarding
this assignment, and that I have not received or given any assistance that is
contrary to the letter or the spirit of the collaboration guidelines for this
assignment.

Dated: January, 31, 2020
*/

// MAIN //
#pragma region
int main(int argc, char const *argv[]) {
  TABLE T;
  set_LOCAL(true);
  set_S1(SEQ1), set_S2(SEQ2);
  set_MATCH(1), set_MISMATCH(-2), set_G(-2), set_H(-5);
  allocate_table(&T) ?: (puts("fail to allocate memory\n"), exit(1));
  align(T);
  print_result();
  printf("Alignment Complete\n");
  return 0;
}
#pragma endregion