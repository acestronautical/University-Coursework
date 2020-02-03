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

#define SEQ1                                                                   \
  "ACATGCTACACGTATCCGATACCCCGTAACCGATAACGATACACAGACCTCGTACGCTTGCTACAACGTACTCT" \
  "ATAACCGAGAACGATTGACATGCCTCGTACACATGCTACACGTACTCCGAT"

#define SEQ2                                                                   \
  "ACATGCGACACTACTCCGATACCCCGTAACCGATAACGATACAGAGACCTCGTACGCTTGCTAATAACCGAGAA" \
  "CGATTGACATTCCTCGTACAGCTACACGTACTCCGAT"

// #define SEQ1 "ACATGCT"

// #define SEQ2 "AACATGCT"

// INCUDES //
#pragma region
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma endregion

// MACROS //
#pragma region
// typeof provides safety
// https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Typeof.html#Typeof
#define MAX2(a, b)                                                             \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

#define MAX3(a, b, c) MAX2(MAX2(a, b), c)
#define MAX4(a, b, c, d) MAX2(MAX2(MAX2(a, b), c), d);
#define NEG_INF INT_MIN + 10000
#pragma endregion

// TYPES //
#pragma region
typedef struct CELL {
  int D, S, I;
} CELL;

typedef struct TABLE {
  CELL **cell;
  int rows_i, cols_j;
} TABLE;
#pragma endregion

// GLOBALS //
#pragma region
// make static so not externally linked
static int _G = 0, _H = 0, _MATCH = 0, _MISMATCH = 0, _MAX = NEG_INF;
static char *_S1 = NULL, *_S2 = NULL;
#pragma endregion

// FORWARD DECLARE FUNCTIONS //
#pragma region
char *set_S1(char *s1);
char *S1(void);
char *set_S2(char *s2);
char *S2(void);
int set_H(const int h);
int H(void);
int set_G(const int g);
int G(void);
int set_MATCH(int match);
int MATCH(void);
int set_MISMATCH(int mismatch);
int MISMATCH(void);
int M(int, int);

bool readin_strings(char **, char **);
bool allocate_table(TABLE *);
bool init_global(TABLE T);
bool init_local(TABLE T);
bool populate_global(TABLE T);
bool populate_local(TABLE T);
void debug_print(TABLE);
#pragma endregion

// MAIN //
#pragma region
int main(int argc, char const *argv[]) {
  TABLE T;
  bool local = false;
  set_S1(SEQ1), set_S2(SEQ2);
  set_MATCH(1), set_MISMATCH(-2), set_G(-2), set_H(-5);
  T.rows_i = strlen(S1()) + 1, T.cols_j = strlen(S2()) + 1;
  allocate_table(&T) ?: (puts("fail to allocate memory\n"), exit(1));
  local ? init_local(T) : init_global(T);
  local ? populate_local(T) : populate_global(T);
  debug_print(T);
  return 0;
}
#pragma endregion

// FUNCTIONS //
#pragma region

// global setters/getters

// Sequences
char *set_S1(char *s1) { return _S1 = s1; }
char *S1(void) { return _S1; }

char *set_S2(char *s2) { return _S2 = s2; }
char *S2(void) { return _S2; }

// Scoring
int set_MAX(const int max) { return _MAX = max; }
int MAX(void) { return _MAX; }

int set_H(const int h) { return _H = h; }
int H(void) { return _H; }

int set_G(const int g) { return _G = g; }
int G(void) { return _G; }

int set_MATCH(int match) { return _MATCH = match; }
int MATCH(void) { return _MATCH; }

int set_MISMATCH(int mismatch) { return _MISMATCH = mismatch; }
int MISMATCH(void) { return _MISMATCH; }

int M(int i, int j) {
  char a = S1()[i - 1];
  char b = S2()[j - 1];
  return a == b ? MATCH() : MISMATCH();
};



// allocate_table: dynamically allocate 2D array
bool allocate_table(TABLE *T) {
  if (!(T->cell = (CELL **)malloc(T->rows_i * sizeof(CELL *))))
    return false;
  for (int i = 0; i < T->rows_i; i++)
    if (!(T->cell[i] = (CELL *)malloc(T->cols_j * sizeof(CELL))))
      return false;
  return true;
}

// init_global:
// S(0,0) = 0, S(i, 0) = NEG_INF, S(0, j) = NEG_INF
// D(0,0) = NEG_INF, D(0, j) = NEG_INF, D(i, 0) = h + i * g
// I(0,0) = NEG_INF, I(0, J) = h + j * g, I(i,0) = NEG_INF
bool init_global(TABLE T) {
  T.cell[0][0].S = 0;
  T.cell[0][0].D = NEG_INF;
  T.cell[0][0].I = NEG_INF;

  for (int i = 1; i < T.rows_i; i++) {
    T.cell[i][0].S = T.cell[i][0].I = NEG_INF;
    T.cell[i][0].D = H() + (i * G());
  }

  for (int j = 1; j < T.cols_j; j++) {
    T.cell[0][j].S = T.cell[0][j].D = NEG_INF;
    T.cell[0][j].I = H() + (j * G());
  }
}

// init_local:
// S(0,0) = S(i, 0) = S(0, j) = 0
// D(0,0) = D(0, j) = D(i, 0) = 0
// I(0,0) = I(0, J) = I(i, 0) = 0
bool init_local(TABLE T) {
  T.cell[0][0].S = 0;
  T.cell[0][0].D = 0;
  T.cell[0][0].I = 0;

  for (int i = 1; i < T.rows_i; i++)
    T.cell[i][0].S = T.cell[i][0].I = T.cell[i][0].D = 0;

  for (int j = 1; j < T.cols_j; j++)
    T.cell[0][j].S = T.cell[0][j].D = T.cell[0][j].I = 0;
}

// populate_global:
// S(i, j)= MAX( S(i-1, j-1),   D(i-1, j-1),       I(i-1, j-1)) + m(a, b)
// D(i, j)= MAX( D(i-1, j) + g, S(i-1, j) + h + g, I(i-1, j) + h + g )
// I(i, j)= MAX( I(i, j-1) + g, S(i, j-1) + h + g, D(i, j-1) + h + g )
bool populate_global(TABLE T) {
  CELL *cur, *zont, *diag, *vert;
  for (int i = 1; i < T.rows_i; i++) {
    for (int j = 1; j < T.cols_j; j++) {
      cur = &T.cell[i][j];

      diag = &T.cell[i - 1][j - 1];
      cur->S = MAX3(diag->S, diag->D, diag->I) + M(i, j);

      vert = &T.cell[i - 1][j];
      cur->D = MAX3(vert->D + G(), vert->S + H() + G(), vert->I + H() + G());

      zont = &T.cell[i][j - 1];
      cur->I = MAX3(zont->I + G(), zont->S + H() + G(), zont->D + H() + G());
    }
  }
}

// populate_local:
// S(i, j)= MAX( S(i-1, j-1),   D(i-1, j-1),       I(i-1, j-1)) + m(a, b) or 0
// D(i, j)= MAX( D(i-1, j) + g, S(i-1, j) + h + g, I(i-1, j) + h + g) or 0
// I(i, j)= MAX( I(i, j-1) + g, S(i, j-1) + h + g, D(i, j-1) + h + g) or 0
bool populate_local(TABLE T) {
  CELL *cur, *zont, *diag, *vert;
  for (int i = 1; i < T.rows_i; i++) {
    for (int j = 1; j < T.cols_j; j++) {
      cur = &T.cell[i][j];

      diag = &T.cell[i - 1][j - 1];
      cur->S = MAX2(MAX3(diag->S, diag->D, diag->I) + M(i, j), 0);

      vert = &T.cell[i - 1][j];
      cur->D = MAX4(vert->D + G(), vert->S + H() + G(), vert->I + H() + G(), 0);

      zont = &T.cell[i][j - 1];
      cur->I = MAX4(zont->I + G(), zont->S + H() + G(), zont->D + H() + G(), 0);
    }
  }
}

// debug_print: prettyish print to csv file
void debug_print(TABLE T) {
  FILE *f = fopen("table.csv", "w");
  CELL *cur;
  fprintf(f, "%c |", ' ');

  for (int j = 0; j < T.cols_j; j++)
    if (j != 0)
      fprintf(f, "%-*c|", 15, S2()[j - 1]);
    else
      fprintf(f, "%-*c|", 15, '0');

  for (int i = 0; i < T.rows_i; i++) {
    if (i != 0)
      fprintf(f, "\n\n%c |", S1()[i - 1]);
    else
      fprintf(f, "\n%c |", '0');

    for (int j = 0; j < T.cols_j; j++) {
      cur = &T.cell[i][j];
      cur->D == NEG_INF ? fprintf(f, "D%-4c", '!')
                        : fprintf(f, "D%-4d", cur->D);
      cur->S == NEG_INF ? fprintf(f, "S%-4c", '!')
                        : fprintf(f, "S%-4d", cur->S);
      cur->I == NEG_INF ? fprintf(f, "I%-4c|", '!')
                        : fprintf(f, "I%-4d|", cur->I);
    }
  }
  fclose(f);
}
#pragma endregion