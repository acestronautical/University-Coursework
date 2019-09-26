#include "keymap2"

#define KCNTL 0x00
#define KSTAT 0x04
#define KDATA 0x08
#define KCLK 0x0C
#define KISTA 0x10

#define CAPSLOCK 0x58
#define LSHIFT 0x12
#define RSHIFT 0x59
#define LCTRL 0x12
#define RCTRL 0xE0

extern int kputc(char c);

typedef volatile struct kbd {
  char *base;
  char buf[128];
  int head, tail, data, room;
} KBD;

volatile KBD kbd;

// state variables
int shift = 0;    // left and right shift key state
int control = 0;  // control key state
int capslock = 0; // caps lock key state
int release = 0;  // key release

int kbd_init() {
  KBD *kp = &kbd;
  kp->base = (char *)0x10006000;
  *(kp->base + KCNTL) = 0x10; // bit4=Enable bit0=INT on
  *(kp->base + KCLK) = 8;
  kp->head = kp->tail = 0;
  kp->data = 0;
  kp->room = 128;
}

void kbd_handler() {
  unsigned char code, c;
  int i;
  KBD *kp = &kbd;

  code = *(kp->base + KDATA);
  // printf("code: %d %x", code, code);

  if (code & 0x80) { // key release: ONLY catch release of shift, control
    release = 1;
    code &= 0x7F; // mask out bit 7
    if (code == LSHIFT || code == RSHIFT)
      shift = 0; // released the shift key
    else if (code == LCTRL)
      control = 0; // released the Control key
    return;
  }

  if (release) {
    release = 0;
    return;
  }

  if (code == LSHIFT || code == RSHIFT) {
    shift = 1;
    return;
  }
  if (code == LCTRL) {
    control = 1;
    return;
  }

  if (code == CAPSLOCK) {
    capslock = !capslock;
    return;
  }

  /* (1). write code to handle caps lock key *******/
  c = ((shift || capslock) ? utab[code] : ltab[code]);

  /* (2). write code to recognize Control-C key *******/
  if (control && c == 'c') { // Control-C keys on PC, these are 2 keys
    printf("Control-c key\n");
    c = '\n'; // force a line, let proc handle #2 signal when exit Kmode
  }

  /* (3). write code to recognize Control-D key *******/
  if (control && c == 'd') { // Control-D, these are 2 keys
    c = 4;                   // Control-D
  }

  // Store char in buf[] for task to get

  if (kp->data == 128) // buf FULL, ignore current key
    return;

  kp->buf[kp->head++] = c;
  kp->head %= 128;

  kp->data++;
}

int kgetc() {
  char c;
  KBD *kp = &kbd;

  while (kp->data == 0)
    ;

  lock();
  c = kp->buf[kp->tail++];
  kp->tail %= 128;
  kp->data--;
  kp->room++;
  unlock();
  kputc(c);
  return c;
}

int kgets(char s[]) {
  char c;
  while ((c = kgetc()) != '\r') {
    *s++ = c;
  }
  *s = 0;
  return strlen(s);
}
