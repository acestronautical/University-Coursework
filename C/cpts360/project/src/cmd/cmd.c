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
    execvp(c->argv, (char *const *)c->argv);
  }
  return pid; // parent
}