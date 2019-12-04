#include "ucode.c"

int main(int argc, char *argv[]) {
  char buf[256];
  int fd;

  if (argc == 1) { 
    while (1) {
      gets(buf);
      if (!strcmp("\0", buf))
        return 0;
      printf("%s\n", buf);
    }
  } else if (argc == 2) { 
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
      printf("CAT: fail to open %s \n", argv[1]);
      return 1;
    }
    while (read(fd, buf, 256) == 256)
      printf("%s", buf);
    printf("%s\n", buf);
  } else {
    printf("CAT: more than one arg not supported\n");
  }
  close(fd);
  exit(0);
}