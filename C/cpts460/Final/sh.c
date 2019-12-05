#include "ucode.c"

int do_pipe(char *line, int *pd_og);
char *pop_pipe(char *line);

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
    while (*linep == ' ')
      linep++;
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
  char *cmd = pop_pipe(line);
  int pd_out[2], pid;
  if (cmd) {
    pipe(pd_out);
    pid = fork();
    // if parent then we read from it
    if (pid) { // parent
      close(pd_out[1]);
      close(0);
      dup(pd_out[0]);
      close(pd_out[0]);
      while (*cmd == ' ')
        cmd++;
      exec(cmd);
    } else
      do_pipe(line, pd_out);
  } else {
    exec(line);
  }
  return 0;
}

char *pop_pipe(char *line) {
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
