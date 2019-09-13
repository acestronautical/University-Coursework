#define TXFE 0x80
#define RXFF 0x40
#define TXFF 0x20
#define RXFE 0x10
#define BUSY 0x08

/******** uart.c file of C2.5 : UART Driver Code ********/
/*** bytes offsets of UART registers from char *base ***/
#define UDR 0x00
#define UFR 0x18

typedef volatile struct uart {
  char *base;
  int n;
  // base address; as char *
  // uart number 0-3
} UART;

UART uart[4]; // 4 UART structures

int uart_init() { // UART initialization function
  int i;
  UART *up;
  for (i = 0; i < 4; i++) {
    // uart0 to uart2 are adjacent
    up = &uart[i];
    up->base = (char *)(0x101F1000 + i * 0x1000);
    up->n = i;
  }
  uart[3].base = (char *)(0x10009000); // uart3 at 0x10009000
}

int ugetc(UART *up)
// input a char from UART pointed by up
{
  while (*(up->base + UFR) & RXFE)
    ;
  // loop if UFR is REFE
  return *(up->base + UDR);
  // return a char in UDR
}

int uputc(UART *up, char c)
// output a char to UART pointed by up
{
  while (*(up->base + UFR) & TXFF)
    ; // loop if UFR is TXFF
  *(up->base + UDR) = c;
  // write char to data register
}

int upgets(UART *up, char *s)
// input a string of chars
{
  while ((*s = ugetc(up)) != '\r') {
    uputc(up, *s);
    s++;
  }
  *s = 0;
}

int uprints(UART *up, char *s) {
  while (*s)
    uputc(up, *s++);
}