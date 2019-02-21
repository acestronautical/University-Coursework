#include "wallClock.h"

void timer_handler(int sig) {
  ss = (ss + 1) % 60;
  mm = (mm + !ss) % 60;
  hh = (hh + (!mm && !ss)) % 24;
  printf("%.2d :%.2d : %.2d\r", hh, mm, ss);
  fflush(stdout);
}

int wallClock() {
  struct itimerval timer;
  time_t now;
  struct tm *now_tm;
  now = time(NULL);
  now_tm = localtime(&now);
  ss = now_tm->tm_sec;
  mm = now_tm->tm_min;
  hh = now_tm->tm_hour;

  signal(SIGALRM, &timer_handler);

  /* Configure the timer to expire after 1 sec */
  timer.it_value.tv_sec = 1;
  timer.it_value.tv_usec = 0;

  /* and every 1 sec after that */
  timer.it_interval.tv_sec = 1;
  timer.it_interval.tv_usec = 0;
  printf("\nWALLCLOCK\n");
  setitimer(ITIMER_REAL, &timer, NULL);

  while (1)
    ;
}

// The program will print timer_handler : signal = 14 once every second.