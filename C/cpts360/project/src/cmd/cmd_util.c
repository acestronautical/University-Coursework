#include "cmd.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int make_cmd(char *line, cmd *c) {
  // split by whitespace into cmd struct
  int i = 0;
  char *s = strtok(line, " ");
  for (; s; i++) {
    c->argv[i] = s;
    s = strtok(NULL, " ");
  }
  c->argc = i;
  // NULL terminate argv
  c->argv[i] = NULL;
  return i;
}

int spawn_proc(int in_fd, int out_fd, cmd *c) {
  pid_t pid = fork();
  if (pid == 0) { // child
    if (in_fd != 0) {
      dup2(in_fd, 0);
      close(in_fd);
    }
    if (out_fd != 1) {
      dup2(out_fd, 1);
      close(out_fd);
    }
    execvp(c->argv[0], (char *const *)c->argv);
  }
  return pid; // parent
}