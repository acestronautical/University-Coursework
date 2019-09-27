#include "type.h"

#include "exceptions.c"
// #include "kbd.c" // use obj
#include "kernel.c"
#include "pipe.c"
#include "queue.c" // include queue.c file
#include "uart.c"
#include "vid.c"

void copy_vectors(void) {
  extern u32 vectors_start;
  extern u32 vectors_end;
  u32 *vectors_src = &vectors_start;
  u32 *vectors_dst = (u32 *)0;
  while (vectors_src < &vectors_end)
    *vectors_dst++ = *vectors_src++;
}

void IRQ_handler() {
  int vicstatus, sicstatus;
  int ustatus, kstatus;

  // read VIC SIV status registers to find out which interrupt
  vicstatus = VIC_STATUS;
  sicstatus = SIC_STATUS;
  if (vicstatus & 0x80000000) {
    if (sicstatus & 0x08) {
      kbd_handler();
    }
  }
}

/*************** main() function ***************/
int main() {
  fbuf_init();
  kprintf("Welcome to Wanix in ARM\n");
  uart_init();
  kbd_init();
  // pipe_init();
  int i;
  kpipe = &pipe;
  kpipe->head = kpipe->tail = 0;
  kpipe->data = 0; kpipe->room = PSIZE;
  // initialize PIPEs
  kpipe = &pipe; // create global kpipe
  init();                // kernel init
  kprintf("P0 kfork tasks\n");
  kfork((int)pipe_writer, 1); // pipe writer process
  kfork((int)pipe_reader, 1); // pipe reader process
  printf("forked pipes\n");
  while (1) {
      tswitch();
  }
}