#include "matrixSum.h"
#include "wallClock.h"
int main(int argc, char *argv[]) {
  initMatrix();
  matrixSumS();
  matrixSumT();
  wallClock();
  return 0;
}

// ========================  Assignment #1: =========================
// In C4.1, change N to 500000. (but do not print the matrix)
// Use gettimeofday() to show its total running time.

// Write a program, s.c, which compute t he sum of the sama matrix as in C4.1
// by a SEQUENTIAL algorithm.

// Use both   time a.out     AND    gettimeofday()
// to compare the run time of the 2 progams.
// ==================================================================

// ============= Assignment #2 =======================================
// Use a mutex lock to protect the update of total in a CRITICAL REGION (CR)
// Verify total is CORRECT no matter how long a thread executes inside the CR.
// ===================================================================

// ============= Assignment #3 =======================================
// Set the timer to fire after 0.5 second, but every 1000 usec after that.
// Display a wall clock in the form of
//           hh : mm : ss
// which is updated once every second.
// ===================================================================