#include "myShell.h"

int initShell() {
  user_name = getenv("USER");
  home_dir = getenv("HOME");
  chdir(home_dir);
  return 0;
};

int writePrompt() {
  write(STDOUT_FILENO, ANSI_COLOR_GREEN, strlen(ANSI_COLOR_GREEN));
  bytes_wrote = write(STDOUT_FILENO, user_name, strlen(user_name));
  bytes_wrote += write(STDOUT_FILENO, ":", 1);
  write(STDOUT_FILENO, ANSI_COLOR_BLUE, strlen(ANSI_COLOR_BLUE));
  bytes_wrote += write(STDOUT_FILENO, cwd, strlen(cwd));
  bytes_wrote += write(STDOUT_FILENO, "$ ", 2);
  write(STDOUT_FILENO, ANSI_COLOR_RESET, strlen(ANSI_COLOR_RESET));
  return bytes_wrote;
}

int writeNewline() { return write(STDOUT_FILENO, "\n\r", 2); }

int readCmd() {
  bytes_read = read(STDIN_FILENO, user_cmd, sizeof(user_cmd));
  user_cmd[bytes_read - 1] = '\0';
  return bytes_read;
}
int pipeCmds(char **head, char **tail) {
  int pd[2];
  pipe(pd);
  pid_t pid = fork();
  if (pid) { // parent
    close(pd[0]);
    close(1);
    dup(pd[1]);
    close(pd[1]);
    exit(execvp(*head, head));
  } else { // child
    close(pd[1]);
    close(0);
    dup(pd[0]);
    close(pd[0]);
    exit(execvp(*tail, tail));
  }
  return 0;
}
int forkExecCmd(char **head, char **tail, char *input, char *output,
                char *append) {
  pid_t parent = getpid();
  pid_t pid = fork();
  int status;

  if (pid == -1) // bad fork
    write(STDOUT_FILENO, "ERR: fork failed", 16);
  else if (pid > 0) // parent
    waitpid(pid, &status, 0);
  else { // child
    if (head)
      exit(pipeCmds(head, tail));
    else {
      if (input) {
        close(0);
        open(input, O_RDONLY);
      }
      if (output) {
        close(1);
        open(output, O_WRONLY | O_CREAT, 0644);
      }
      if (append) {
        close(1);
        open(append, O_WRONLY | O_APPEND);
      }
      exit(execvp(*cmdv, cmdv));
    }
  }
  return status;
}

int doCmd() {
  char *s, *input = NULL, *output = NULL, *append = NULL, **head = NULL,
           **tail = NULL;
  // parse
  s = strtok(user_cmd, " ");
  for (cmdc = 0; s; cmdc++) {
    cmdv[cmdc] = s;
    s = strtok(NULL, " ");
    if (s && !strcmp(s, "<")) { // in
      s = strtok(NULL, " ");
      input = s;
      s = strtok(NULL, " ");
    } else if (s && !strcmp(s, ">")) { // out
      s = strtok(NULL, " ");
      output = s;
      s = strtok(NULL, " ");
    } else if (s && !strcmp(s, ">>")) { // append
      s = strtok(NULL, " ");
      append = s;
      s = strtok(NULL, " ");
    } else if (s && !strcmp(s, "|")) { // pipe
      s = strtok(NULL, " ");
      head = &cmdv[0];
      cmdv[++cmdc] = NULL;
      tail = &cmdv[cmdc + 1];
    }
  }
  cmdv[cmdc] = NULL;

  // run
  if (cmdv[0] && !strcmp(cmdv[0], "cd"))
    if (cmdc > 1)
      chdir(cmdv[1]);
    else
      chdir(home_dir);
  else if (cmdv[0] && !strcmp(cmdv[0], "exit"))
    exit(0);
  else
    forkExecCmd(head, tail, input, output, append);

  return 0;
}
int startShell() {
  char user_cmd[1024];
  initShell();
  while (1) {
    getcwd(cwd, sizeof(cwd));
    writePrompt();
    readCmd();
    doCmd();
  }
  return 0;
}
