/* itimer.c program */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

/*************************
 struct timeval {
    time_t      tv_sec;         // seconds
    suseconds_t tv_usec;        // microseconds
 };
 struct itimerval {
    struct timeval it_interval; // Interval of periodic timer
    struct timeval it_value;    // Time until next expiration
 };
*********************/

int hh, mm, ss;
void timer_handler(int sig);
int wallClock();