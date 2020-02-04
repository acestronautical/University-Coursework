#include "alignment.h"

/*
CptS 471/571 Assignment Cover Sheet

Assignment: Programming Project 1
Name: Cassidy, Ace

https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Typeof.html#Typeof
https://stackoverflow.com/questions/3161054/static-and-external-variables


I certify that I have listed above all the sources that I consulted regarding
this assignment, and that I have not received or given any assistance that is
contrary to the letter or the spirit of the collaboration guidelines for this
assignment.

Dated: January, 31, 2020
*/

// MAIN //
#pragma region
int main(int argc, char const *argv[]) {
  // Arg handling
  argc == 3 ?: (puts("Usage:<executable><file><0:global, 1:local>"), exit(1));
  FILE *f = fopen(argv[1], "r");
  f ?: (puts("Fail to open file"), exit(1));
  set_LOCAL(*argv[2] == '1' ? true : false);
  printf("Begin %s alignment\n",
         *argv[2] == '1' ? "local" : "global");

  // Alignment
  TABLE T;
  read_SEQS(f);
  fclose(f);
  set_MATCH(1), set_MISMATCH(-2), set_GAP(-2), set_OPEN(-5);
  allocate_table(&T) ?: (puts("fail to allocate memory\n"), exit(1));
  align(T);
  print_result();
  printf("Alignment Complete\n");
  return 0;
}
#pragma endregion