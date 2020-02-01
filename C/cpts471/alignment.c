/*
CptS 471/571 Assignment Cover Sheet

Assignment: Programming Project 1
Name: Cassidy, Ace

I certify that I have listed above all the sources that I consulted regarding
this assignment, and that I have not received or given any assistance that is
contrary to the letter or the spirit of the collaboration guidelines for this
assignment.

Dated: January, 31, 2020
*/

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define SEQ1                                                                   \
//   "ACATGCTACACGTATCCGATACCCCGTAACCGATAACGATACACAGACCTCGTACGCTTGCTACAACGTACTCT" \
//   "ATAACCGAGAACGATTGACATGCCTCGTACACATGCTACACGTACTCCGAT"

// #define SEQ2                                                                   \
//   "ACATGCGACACTACTCCGATACCCCGTAACCGATAACGATACAGAGACCTCGTACGCTTGCTAATAACCGAGAA" \
//   "CGATTGACATTCCTCGTACAGCTACACGTACTCCGAT"

#define SEQ1 "ACATGCTACACGTATCCGATACCCCG"

#define SEQ2 "ACATGCGACACTACTCCGATACCCTAA"

typedef struct CELL {
  int D, S, I;
} cell;

// I'll handle I/O later
bool readin_strings(char **s1, char **s2) {
  *s1 = SEQ1;
  *s2 = SEQ2;
  return true;
}

// dynamically allocate 2D array
bool allocate_2D(cell ***arr, const int rows, const int cols) {
  (*arr) = (cell **)calloc(rows, sizeof(cell *));
  if (!(*arr))
    return false;
  for (int i = 0; i < rows; i++) {
    (*arr)[i] = (cell *)calloc(cols, sizeof(cell));
    if (!(*arr)[i])
      return false;
  }
  return true;
}

bool init_global(cell **table, const int row, const int col) {}

bool init_local(cell **table, const int row, const int col, int h, int g) {
  for (int i = 1; i < row; i++) {
    table[i][0].S = table[i][0].I = INT_MIN;
    table[i][0].D = h + (g * (i));
  }
  for (int j = 1; j < col; j++) {
    table[0][j].S = table[0][j].D = INT_MIN;
    table[0][j].I = h + (g * (j));
  }
}

void debug_print(cell **table, int row, int col) {
  FILE *f = fopen("table.csv", "w");
  for (int i = 0; i <= col; i++)
    fprintf(f, "%-36d,", i);
  for (int i = 0; i < row; i++) {
    fprintf(f, "\n\n%-36d,", i+1);
    for (int j = 0; j < col; j++) {
      fprintf(f, "D%-11dS%-11dI%-11d,", table[i][j].D, table[i][j].S, table[i][j].I);
    }
  }
  fclose(f);
}

int main(int argc, char const *argv[]) {
  cell **table;
  char *S1, *S2;
  int match = 1, mismatch = -2, h = -5, g = -2;
  bool local = true;

  readin_strings(&S1, &S2) ?: (puts("fail to read s1 s2\n"), exit(1));
  int lenS1 = strlen(S1), lenS2 = strlen(S2), row = lenS1 + 1, col = lenS2 + 1;
  allocate_2D(&table, row, col) ?: (puts("fail allocate memory\n"), exit(1));
  local ? init_local(table, row, col, h, g) : init_global(table, row, col);
  debug_print(table, row, col);
  return 0;
}
