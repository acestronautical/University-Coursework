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

char *SEQ1 =
    "ACATGCTACACGTATCCGATACCCCGTAACCGATAACGATACACAGACCTCGTACGCTTGCTACAAC"
    "GTACTCTATAACCGAGAACGATTGACATGCCTCGTACACATGCTACACGTACTCCGAT";

char *SEQ2 = "ACATGCGACACTACTCCGATACCCCGTAACCGATAACGATACAGAGACCTCGTACGCTTGC"
             "TAATAACCGAGAA"
             "CGATTGACATTCCTCGTACAGCTACACGTACTCCGAT";

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
#define MAX4(a, b, c, d) MAX2(MAX3(a, b, c), d);
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
// make all static so not externally linked

// flags
static bool _LOCAL = false;
// scoring
static int _G = 0, _H = 0, _MATCH = 0, _MISMATCH = 0;
// alignment stats
static int _OPTIMAL_SCORE = NEG_INF, _OPTIMAL_J = NEG_INF, _OPTIMAL_I = NEG_INF,
           _MATCHES, _MISMATCHES, _GAPS, _OPENINGS;
// sequences
static char *_S1_i = NULL, *_S2_j = NULL, *_TRACE_S1_i = NULL,
            *_TRACE_S2_j = NULL, *_TRACE_COMP = NULL;
#pragma endregion

// FORWARD DECLARE FUNCTIONS //
#pragma region
char *set_S1(char *);
char *set_S2(char *);
bool set_LOCAL(bool);
int set_H(const int);
int set_G(const int);
int set_MATCH(int);
int set_MISMATCH(int);
int OPTIMAL(void);
int MATCHES(void);
int MISMATCHES(void);
int GAPS(void);
int OPENINGS(void);
int M(int, int);
void rev_str(char *);
bool allocate_table(TABLE *);
bool init_global(TABLE);
bool init_local(TABLE);
bool populate_global(TABLE);
bool populate_local(TABLE);
void *trace_global(TABLE);
void debug_print(TABLE);
#pragma endregion

// MAIN //
#pragma region
int main(int argc, char const *argv[]) {
  TABLE T;
  set_LOCAL(false);
  set_S1(SEQ1), set_S2(SEQ2);
  set_MATCH(1), set_MISMATCH(-2), set_G(-2), set_H(-5);
  allocate_table(&T) ?: (puts("fail to allocate memory\n"), exit(1));
  _LOCAL ? init_local(T) : init_global(T);
  _LOCAL ? populate_local(T) : populate_global(T);
  debug_print(T);
  trace_global(T);
  FILE *f = fopen("result.txt", "w");
  fprintf(f, "%s\n", _TRACE_S1_i);
  fprintf(f, "%s\n", _TRACE_COMP);
  fprintf(f, "%s\n", _TRACE_S2_j);
  fprintf(f, "%s optimal score: %d\n", _LOCAL ? "Local" : "Global",
          _OPTIMAL_SCORE);
  fclose(f);
  return 0;
}
#pragma endregion

// FUNCTIONS //
#pragma region

// global setters/getters

// Sequences
char *set_S1(char *s1) { return _S1_i = s1; }
char *set_S2(char *s2) { return _S2_j = s2; }

// Flags
bool set_LOCAL(bool local) { return _LOCAL = local; }

// Scoring
int set_H(const int h) { return _H = h; }
int set_G(const int g) { return _G = g; }
int set_MATCH(int match) { return _MATCH = match; }
int set_MISMATCH(int mismatch) { return _MISMATCH = mismatch; }

// Stats
int OPTIMAL(void) { return _OPTIMAL_SCORE; }
int MATCHES(void) { return _MATCHES; }
int MISMATCHES(void) { return _MISMATCHES; }
int GAPS(void) { return _GAPS; }
int OPENINGS(void) { return _OPENINGS; }

// M: calculate match or not match score off a table index
int M(int i, int j) {
  char a = _S1_i[i - 1];
  char b = _S2_j[j - 1];
  return a == b ? _MATCH : _MISMATCH;
};

// rev_str: reverse string in place, excerpted from SO because i've written this
// function so many times
void rev_str(char *s) {
  char t, *e = s + strlen(s);
  while (--e > s) {
    t = *s;
    *s++ = *e;
    *e = t;
  }
}

// allocate_table: dynamically allocate 2D array
bool allocate_table(TABLE *T) {
  T->rows_i = strlen(_S1_i) + 1, T->cols_j = strlen(_S2_j) + 1;
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
    T.cell[i][0].D = _H + (i * _G);
  }

  for (int j = 1; j < T.cols_j; j++) {
    T.cell[0][j].S = T.cell[0][j].D = NEG_INF;
    T.cell[0][j].I = _H + (j * _G);
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
      cur->D = MAX3(vert->D + _G, vert->S + _H + _G, vert->I + _H + _G);

      zont = &T.cell[i][j - 1];
      cur->I = MAX3(zont->I + _G, zont->S + _H + _G, zont->D + _H + _G);
    }
  }
  // Set last cell to be the optimal for global alignment
  int o = MAX3(cur->D, cur->I, cur->S);
  _OPTIMAL_SCORE = o, _OPTIMAL_I = T.rows_i - 1, _OPTIMAL_J = T.cols_j - 1;
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
      cur->D = MAX4(vert->D + _G, vert->S + _H + _G, vert->I + _H + _G, 0);

      zont = &T.cell[i][j - 1];
      cur->I = MAX4(zont->I + _G, zont->S + _H + _G, zont->D + _H + _G, 0);

      int o = MAX4(cur->D, cur->I, cur->S, _OPTIMAL_SCORE);
      if (o > _OPTIMAL_SCORE)
        _OPTIMAL_SCORE = o, _OPTIMAL_I = i, _OPTIMAL_J = j;
    }
  }
}

void *trace_global(TABLE T) {
  _MATCHES = 0, _MISMATCHES = 0, _GAPS = 0, _OPENINGS = 0;
  _TRACE_S1_i = (char *)calloc(sizeof(char), T.rows_i + T.cols_j);
  _TRACE_S2_j = (char *)calloc(sizeof(char), T.rows_i + T.cols_j);
  _TRACE_COMP = (char *)calloc(sizeof(char), T.rows_i + T.cols_j);
  int i = T.rows_i - 1, j = T.cols_j - 1, pos = 0, m = 0;
  CELL *cur = &T.cell[i][j], *prev;
  int score = MAX3(cur->S, cur->D, cur->I);
  while (i > 0 | j > 0) {

    if (cur->S == score) { // substitution / diag
      m = M(i, j);
      m == _MATCH ? _MATCHES++ : _MISMATCHES++;
      _TRACE_S1_i[pos] = _S1_i[i - 1];
      _TRACE_S2_j[pos] = _S2_j[j - 1];
      _TRACE_COMP[pos] = m == _MATCH ? '|' : ' ';

      i--, j--;
      prev = &T.cell[i][j];
      if (cur->S == (prev->D + m)) {
        score = prev->D;
      } else if (cur->S == (prev->S + m)) {
        score = prev->S;
      } else {
        score = prev->I;
      }

    } else if (cur->D == score) { // deletion / vert
      _TRACE_S1_i[pos] = _S1_i[i - 1];
      _TRACE_S2_j[pos] = '_';
      _TRACE_COMP[pos] = ' ';
      _GAPS++;

      i--;
      prev = &T.cell[i][j];

      if (cur->D == (prev->D + _G)) {
        score = prev->D;
      } else if (cur->D == (prev->S + _H + _G)) {
        score = prev->S;
        _OPENINGS++;
      } else {
        score = prev->I;
        _OPENINGS++;
      }

    } else { // insertion / zont
      _TRACE_S1_i[pos] = '_';
      _TRACE_S2_j[pos] = _S2_j[j -1 ];
      _TRACE_COMP[pos] = ' ';
      _GAPS++;

      j--;
      prev = &T.cell[i][j];

      if (cur->I == (prev->D + _G + _H)) {
        score = prev->D;
        _OPENINGS++;
      } else if (cur->I == (prev->S + _H + _G)) {
        score = prev->S;
        _OPENINGS++;
      } else {
        score = prev->I;
      }
    }
    pos++;
    cur = prev;
  }
  // null terminate
  _TRACE_S1_i[pos] = _TRACE_S2_j[pos] = _TRACE_COMP[pos] = 0;
  // reverse
  rev_str(_TRACE_S1_i), rev_str(_TRACE_S2_j), rev_str(_TRACE_COMP);
}

// debug_print: prettyish print to csv file
void debug_print(TABLE T) {
  FILE *f = fopen("table.csv", "w");
  CELL *cur;
  fprintf(f, "%c |", ' ');

  for (int j = 0; j < T.cols_j; j++)
    if (j != 0)
      fprintf(f, "%-*c|", 15, _S2_j[j - 1]);
    else
      fprintf(f, "%-*c|", 15, '0');

  for (int i = 0; i < T.rows_i; i++) {
    if (i != 0)
      fprintf(f, "\n\n%c |", _S1_i[i - 1]);
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