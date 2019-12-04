#include "ucode.c"
int main(int argc, char *argv[]) {
  int fd1, fd2;
  char c[1];
  if (argc == 1) {
    printf("CP: not enough arguments\n");
    exit(0);
  } else if (argc == 2) {
    fd1 = open(argv[1], O_RDONLY);
    fd2 = 1;
  } else {
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_WRONLY | O_CREAT);
  }
  if (fd1 < 0 || fd2 < 0) {
    printf("Error opening file.\n");
    return 1;
  }
  char buf[1024];
  int n;
  do {
    n = read(fd1, buf, 1024);
    // printf("got: %s", buf);
    if (argc == 2)
      printf("%s", buf);
    else
      write(fd2, buf, 1024);

  } while (n == 1024);
  close(fd1);
  close(fd2);
  return 1;
}