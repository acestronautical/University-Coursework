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

// Colors
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Types
struct command {
  int argc;
  const char *argv[64];
};

// Globals
struct statvfs fs_info;
char cwd[1024];
char *user_name;
char *home_dir;

// Functions
int init_shell() {
  statvfs("/", &fs_info);
  user_name = getenv("USER");
  home_dir = getenv("HOME");
  chdir(home_dir);
  getcwd(cwd, sizeof(cwd));
  return 0;
};

int write_prompt(int fd) {
  char buf[fs_info.f_bsize];
  snprintf(buf, fs_info.f_bsize, "%s%s%s%s%s%s%s", ANSI_COLOR_GREEN, user_name,
           ":", ANSI_COLOR_BLUE, cwd, "$ ", ANSI_COLOR_RESET);
  return write(fd, buf, strlen(buf));
}

int spawn_proc(int in_fd, int out_fd, struct command *c) {
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

int handle_pipes(int out_fd, int in_fd, int n_cmds, struct command *cmds) {
  int i;
  pid_t pid;
  int in, fd[2];

  in = in_fd;
  for (i = 0; i < n_cmds - 1; ++i) {
    pipe(fd);
    spawn_proc(in, fd[1], cmds + i);
    close(fd[1]);
    in = fd[0];
  }
  dup2(in, 0);
  dup2(out_fd, 1);
  return execvp(cmds[i].argv[0], (char *const *)cmds[i].argv);
}

int handle_cmds(int cmdc, struct command *cmdv) {
  // check for cd or exit special cases
  if (!strcmp(cmdv[0].argv[0], "cd")) {
    if (cmdv[0].argc > 1)
      chdir(cmdv[0].argv[1]);
    else
      chdir(home_dir);
    getcwd(cwd, sizeof(cwd));
  } else if (!strcmp(cmdv[0].argv[0], "exit"))
    exit(0);

  // do cmd
  int status;
  pid_t pid = fork();
  if (pid == 0)
    exit(handle_pipes(STDOUT_FILENO, STDIN_FILENO, cmdc, cmdv));
  else
    waitpid(pid, &status, 0);
  return 0;
}

int parse_input(char *user_input, int *cmdc, struct command *cmdv) {

  // split by pipes
  char *cmd_strings[64];
  int cmd_stringc = 0;
  char *s = NULL;
  s = strtok(user_input, "|");
  for (; s; cmd_stringc++) {
    cmd_strings[cmd_stringc] = s;
    s = strtok(NULL, "|");
  }

  // split by whitespace
  struct command *cmd;
  int i = 0;
  int j = 0;
  for (; i < cmd_stringc; i++) {
    cmd = &cmdv[i];
    j = 0;
    s = strtok(cmd_strings[i], " ");
    for (; s; j++) {
      cmd->argv[j] = s;
      s = strtok(NULL, " ");
    }
    cmd->argc = j;
    cmd->argv[j] = NULL;
  }
  *cmdc = i;
  return *cmdc;
}

int start_shell() {
  init_shell();
  char user_input[1024];
  int bytes_read;
  struct command cmdv[64];
  int cmdc;
  while (1) {
    write_prompt(STDOUT_FILENO);
    bytes_read = read(STDIN_FILENO, user_input, 1024);
    user_input[bytes_read - 1] = '\0';
    parse_input(user_input, &cmdc, cmdv);
    handle_cmds(cmdc, cmdv);
  }
  return 0;
}

// int main(int argc, char *argv[]) {
//   start_shell();
//   return 0;
// }