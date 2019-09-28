#include "string.c"
#include "type.h"
// #include "queue.c"  // use provided queue.obj  during linking
// #include "kbd.c"    // use provided kbd.obj    during linking
#include "exceptions.c"
#include "kernel.c"
#include "timer.c"
#include "tqe.c"
#include "vid.c"

void copy_vectors(void) {
  extern u32 vectors_start;
  extern u32 vectors_end;
  u32 *vectors_src = &vectors_start;
  u32 *vectors_dst = (u32 *)0;

  while (vectors_src < &vectors_end)
    *vectors_dst++ = *vectors_src++;
}
int kprintf(char *fmt, ...);

TIMER *tp[4]; // 4 TIMER structure pointers

void IRQ_handler() {
  int vicstatus, sicstatus;
  int ustatus, kstatus;

  // read VIC status register to find out which interrupt
  vicstatus = VIC_STATUS; // VIC_STATUS=0x10140000=status reg
  sicstatus = SIC_STATUS;
  if (vicstatus & 0x80000000) {
    if (sicstatus & 0x08) {
      kbd_handler();
    }
  }
  // VIC status BITs: timer0,1=4, uart0=13, uart1=14
  if (vicstatus & (1 << 4)) {
    // bit4=1:timer0,1
    if (*(tp[0]->base + TVALUE) == 0) // timer 0
      timer_handler(0);
    if (*(tp[1]->base + TVALUE) == 0) // timer 1
      timer_handler(1);
  }
  if (vicstatus & (1 << 5)) {
    // bit5=1:timer2,3
    if (*(tp[2]->base + TVALUE) == 0)
      // timer 2
      timer_handler(2);
    if (*(tp[3]->base + TVALUE) == 0)
      // timer 3
      timer_handler(3);
  }
}

int body();

int main() {
  color = WHITE;
  row = col = 0;

  fbuf_init(); // initialize LCD driver
  kbd_init();  // initialize KBD driver

  /* enable timer0,1, uart0,1 SIC interrupts */

  /* enable VIC for timer interrupts */
  VIC_INTENABLE = 0;
  VIC_INTENABLE |= (1 << 4);  // timer0,1 at bit4
  VIC_INTENABLE |= (1 << 5);  // timer2,3 at bit5
  VIC_INTENABLE |= (1 << 31); // SIC to VIC's IRQ31

  /* enable KBD IRQ */
  SIC_ENSET = 1 << 3;    // KBD int=3 on SIC
  SIC_PICENSET = 1 << 3; // KBD int=3 on SIC

  init(); // init procs and start p0

  timer_init();
  for (int i = 0; i < 1; i++) { // start all 4 timers
    tp[i] = &timer[i];
    timer_start(i);
  }

  //   for (int i = 0; i < 4; i++)
  //  kfork((int)body, 1);

  while (1) {
    //  if (readyQueue)
    // tswitch();
  }
}
