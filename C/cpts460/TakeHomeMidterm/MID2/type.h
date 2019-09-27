// defines.h file
#pragma once

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define UART0_BASE_ADDR 0x101f1000
#define UART0_DR   (*((volatile u32 *)(UART0_BASE_ADDR + 0x000)))
#define UART0_FR   (*((volatile u32 *)(UART0_BASE_ADDR + 0x018)))
#define UART0_IMSC (*((volatile u32 *)(UART0_BASE_ADDR + 0x038)))

#define UART1_BASE_ADDR 0x101f2000
#define UART1_DR   (*((volatile u32 *)(UART1_BASE_ADDR + 0x000)))
#define UART1_FR   (*((volatile u32 *)(UART1_BASE_ADDR + 0x018)))
#define UART1_IMSC (*((volatile u32 *)(UART1_BASE_ADDR + 0x038)))

#define KBD_BASE_ADDR 0x10006000
#define KBD_CR (*((volatile u32 *)(KBD_BASE_ADDR + 0x000)))
#define KBD_DR (*((volatile u32 *)(KBD_BASE_ADDR + 0x008)))

#define TIMER0_BASE_ADDR 0x101E2000
#define TIMER0_LR (*((volatile u32 *)(UART0_BASE_ADDR + 0x000)))
#define TIMER0_BR (*((volatile u32 *)(UART0_BASE_ADDR + 0x032)))

#define VIC_BASE_ADDR 0x10140000
#define VIC_STATUS    (*((volatile u32 *)(VIC_BASE_ADDR + 0x000)))
#define VIC_INTENABLE (*((volatile u32 *)(VIC_BASE_ADDR + 0x010)))
#define VIC_VADDR     (*((volatile u32 *)(VIC_BASE_ADDR + 0x030)))

#define SIC_BASE_ADDR 0x10003000
#define SIC_STATUS    (*((volatile u32 *)(SIC_BASE_ADDR + 0x000)))
#define SIC_INTENABLE (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_ENSET     (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_PICENSET  (*((volatile u32 *)(SIC_BASE_ADDR + 0x020)))

#define BLUE   0
#define GREEN  1
#define RED    2
#define CYAN   3
#define YELLOW 4
#define PURPLE 5
#define WHITE  6

#define  SSIZE 1024

#define  FREE   0
#define  READY  1
#define  SLEEP  2
#define  BLOCK  3
#define  ZOMBIE 4
#define  printf  kprintf

typedef struct proc{
    struct proc *next;      // next proc pointer       
    int  *ksp;              // saved sp: at byte offset 4 
    int   pid;              // process ID
    int   ppid;             // parent process pid 
    int   status;           // PROC status=FREE|READY, etc. 
    int   priority;         // scheduling priority 

    int   event;            // event value to sleep on
    int   exitCode;         // exit value

    struct proc *child;     // first child PROC pointer       
    struct proc *sibling;   // sibling PROC pointer  
    struct proc *parent;    // parent PROC pointer       

    int   kstack[1024];     // process stack                 
}PROC;


// assembly/lib functions

void lock(void);
void unlock(void);
void int_on(int);
int int_off(void);
int kgets(char s[]);
int kputc(char c);

// uart.c globals

#define UDR 0x00
#define UFR 0x18

#define RXFE 0x10
#define TXFF 0x20

typedef struct uart {
  char *base;
  int n;
} UART;

UART uart[4];
char *tab = "0123456789ABCDEF";

// vid.c globals

// char *tab = "0123456789ABCDEF";
u8 cursor;
int volatile *fb;
u8 *font;
int row, col;
int color;

// 
int body();
int tswitch();
int do_exit();

#define NPROC 9

PROC proc[NPROC]; // NPROC PROCs
PROC *freeList;   // freeList of PROCs
PROC *readyQueue; // priority queue of READY procs
PROC *running;    // current running proc pointer
PROC *sleepList;

int procsize = sizeof(PROC);

#define printf kprintf
#define gets kgets

// queue.c

int enqueue(PROC **queue, PROC *p);
PROC *dequeue(PROC **queue);
int printList(char *name, PROC *list);

//
int uprintf(char *fmt, ...);

// pipe stuff

#define NPIPE 2
#define PSIZE 16

typedef struct pipe{
  char buf[PSIZE];
  int head, tail;
  int data, room;
  int status;
}PIPE;


PIPE *kpipe;
PIPE pipe;
