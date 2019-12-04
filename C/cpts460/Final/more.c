#include "ucode.c"

void print_line(int fd) {
  char s[512];
  readline(fd, s);
  printf("%s", s);
}

void print_page(int fd) {
  char buf[513];
  buf[512] = 0;
  int n;
  n = read(fd, buf, 512);
  printf("%s", buf);
  if (n < 512)
    exit(0);
}

int main(int argc, char *argv[]) {
  char tty[64], c;
  int fd, status;

  if (argc == 1) {
    fd = dup(0);
    close(0);
    gettty(tty);
    open(tty, O_RDONLY);
  } else
    fd = open(argv[1], O_RDONLY);

  if (fd < 0)
    return printf("MORE: fail to open %s\n", argv[1]);

  print_page(fd);

  while (1) {
    c = getc();
    switch (c) {
    case '\r':
      print_line(fd);
      break;
    case ' ':
      print_page(fd);
      break;
    case 'q':
      printf(" \n");
      return 1;
    }
  }

  return 1;
}