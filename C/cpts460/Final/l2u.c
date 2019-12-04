#include "ucode.c"
int main(int argc, char *argv[]) {
  int fd1, fd2;
  char c[1];
  if (argc == 1) {
    printf("L2U: not enough arguments\n");
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
  char line[1024];
  while (readline(fd1, line)) {
    // printf("got line: %s\n", line);
    for (int i = 0; i < 512; i++) {
      if (line[i] > 96 && line[i] < 123)
        line[i] -= 32;
    }
    // printf("line now: %s\n", line);
    if (argc == 2)
      printf("%s", line);
    else
      write(fd2, line, 1024);
  }
  close(fd1);
  close(fd2);
  return 1;
}