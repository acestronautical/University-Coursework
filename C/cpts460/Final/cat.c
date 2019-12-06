#include "ucode.c"

#define PROG_NAME "CAT"
int fd;

void setup(int argc, char *argv[]) {
  if (argc == 1)
    fd = STDIN;
  else if (argc == 2) {
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
      printf("%s: fail to open %s \n", PROG_NAME, argv[1]);
      exit(1);
    }
  } else if (argc > 2) {
    printf("%s: too many args\n", PROG_NAME);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  char buf[1];
  STAT stat_buf, *sptr = &stat_buf;
  int n, r;
  setup(argc, argv);
  r = fstat(STDOUT, (char *)sptr);
  while (read(fd, buf, 1)) {
    if (S_ISREG(sptr->st_mode))
      write(STDOUT, buf, 1);
    else
      printf("%c", *buf);
  }
  exit(0);
}