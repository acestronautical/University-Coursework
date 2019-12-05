#include "ucode.c"

int do_pipe(char *line, int *pd_og);
char *pop_tail(char *line);
int handle_command(char *cmd);

int main(int argc, char *argv[]) {
  char line[256], linecp[256], *linep;
  char *line_tokens[32];
  char cwd[256];
  int child_pid, status;
  while (1) {
    getcwd(cwd);
    printf("%s: ", cwd);
    gets(line);
    linep = line;
    trimws(&linep);
    if (!*linep)
      continue;

    strcpy(linecp, line);
    split(linecp, line_tokens, ' ');
    if ((!strcmp(linep, "exit")) || (!strcmp(linep, "logout"))) {
      exit(0);
    }
    if (!strcmp(line_tokens[0], "cd")) {
      if (line_tokens[1])
        chdir(line_tokens[1]);
      else
        chdir("/");
    }

    child_pid = fork();
    if (child_pid) // parent
      while (child_pid != wait(&status))
        ;
    else { // child
      do_pipe(linep, 0);
      exit(0);
    }
  }
}

int do_pipe(char *line, int *pd_in) {
  // if pipe then we write to it
  if (pd_in) {
    close(pd_in[0]);
    close(1);
    dup(pd_in[1]);
    close(pd_in[1]);
  }
  // divide line into head, tail
  char *tail = pop_tail(line);
  int pd_out[2], pid;
  if (tail) {
    pipe(pd_out);
    pid = fork();
    // if parent then we read from it
    if (pid) { // parent
      close(pd_out[1]);
      close(0);
      dup(pd_out[0]);
      close(pd_out[0]);
      trimws(&tail);
      handle_command(tail);
    } else
      do_pipe(line, pd_out);
  } else {
    handle_command(line);
  }
  return 0;
}

char *redirect_io(char *cmd) {
  char *cmdp, rune;
  int fmode;
  for (cmdp = cmd; *cmdp && *cmdp != '<' && *cmdp != '>'; cmdp++)
    ;
  rune = *cmdp;
  if (rune == 0)
    return 0;
  else {
    *cmdp++ = 0;
    if (rune == '>') {
      close(STDOUT);
      if (*cmdp == '>') {
        *cmdp++ = 0;
        fmode = O_WRONLY | O_APPEND;
      } else
        fmode = O_WRONLY | O_CREAT;
    } else if (rune == '<') {
      close(STDIN);
      fmode = O_RDONLY;
    }
  }
  trimws(&cmdp);
  open(cmdp, fmode);
  return cmdp;
}

int handle_command(char *cmd) {
  redirect_io(cmd);
  exec(cmd);
  exit(0);
}

char *pop_tail(char *line) {
  char *linep = line;
  for (; *linep; linep++)
    ;
  for (; *linep != '|' && linep != line; linep--)
    ;

  if (linep == line)
    return 0;
  *linep = 0;
  return ++linep;
}
