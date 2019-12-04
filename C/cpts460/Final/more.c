#include "ucode.c"

void _line(int fd) {
  char *c;
  do {
    if (read(fd, c, 1) == 0)
      exit(0);
    printf("%s", c);
  } while (*c != '\n' && *c != '\r');
}

void _page(int fd) {
  char buf[257];
  buf[256] = 0;
  int n;
  n = read(fd, buf, 256);
  printf("%s", buf);
  if (n < 256)
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
    return printf("File '%s' not found.\n", argv[1]);

  _page(fd);

  if (status == -1) // That first print page might have been it.
    return 1;

  while (1) {
    c = getc();
    switch (c) {
    case '\r':
      _line(fd);
      break;
    case ' ':
      _page(fd);
      break;
    case 'q':
      printf(" \n");
      return 1;
    }
  }

  return 1;
}