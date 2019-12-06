/* cat.c */
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
/* cp.c */
#include "ucode.c"
#define PROG_NAME "CP"
int fd1, fd2;
void setup(int argc, char *argv[]) {
  if (argc == 1) {
    printf("%s: not enough arguments\n", PROG_NAME);
    exit(1);
  } else if (argc == 2) {
    fd1 = open(argv[1], O_RDONLY);
    fd2 = STDOUT;
  } else {
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_WRONLY | O_CREAT);
  }
  if (fd1 < 0 || fd2 < 0) {
    printf("%s: fail to open file.\n", PROG_NAME);
    exit(1);
  }
}
int main(int argc, char *argv[]) {
  char buf[256];
  int n;
  setup(argc, argv);
  do {
    n = read(fd1, buf, 256);
    write(fd2, buf, n);
  } while (n == 256);
  exit(0);
}

/* crt0.c */
int argc;
char *argv[32];
extern int main();
void token(char *line) {
  char *cp;
  cp = line;
  argc = 0;

  while (*cp != 0) {
    while (*cp == ' ')
      *cp++ = 0;
    if (*cp != 0)
      argv[argc++] = cp;
    while (*cp != ' ' && *cp != 0)
      cp++;
    if (*cp != 0)
      *cp = 0;
    else
      break;
    cp++;
  }
  argv[argc] = 0;
}
void showarg(int argc, char *argv[]) {
  int i;
  printf("argc=%d ", argc);
  for (i = 0; i < argc; i++)
    // printf("argv[%d]=%s ", i, argv[i]);
    printf("%s ", argv[i]);
  prints("\n");
}
// BEFORE: r0 was trashed in goUmode(), so had to rely on r1->string
// NOW: r0 is NOT trashed in goUmode() ==> should be r0 alone
void main0(char *s) {
  if (s) {
    // printf("s=%s\n", s);
    token(s);
  }
  // showarg(argc, argv);
  main(argc, argv);
}

/* grep.c */
#include "ucode.c"
int matchstar();
int matchhere();
int match();
#define PROG_NAME "GREP"
int fd;
char *pattern;
void setup(int argc, char *argv[]) {
  if (argc == 1) {
    printf("%s: not enough arguments\n", PROG_NAME);
    exit(1);
  } else if (argc == 2) {
    pattern = argv[1];
    fd = STDIN;
  } else if (argc = 3) {
    pattern = argv[1];
    fd = open(argv[2], O_RDONLY);
  } else {
    printf("%s: too many arguments\n", PROG_NAME);
    exit(1);
  }
  if (fd < 0) {
    printf("%s: fail to open %s\n", PROG_NAME, argv[2]);
    exit(1);
  }
}
int main(int argc, char *argv[]) {
  char line[256];
  int matches = 0, n, lineno = 0;
  setup(argc, argv);
  do {
    lineno++;
    n = readline(fd, line);
    if (match(pattern, line)) {
      printf("line %d: %s", lineno, line);
      matches++;
    }
  } while (*line && n);
  printf("%d matches found\n", matches);
  exit(0);
}
// MATCHING CODE
// Inspired by code from Rob Pikes "The Practice of Programming"
// c    matches any literal character c
// .    matches any single character
// ^    matches the beginning of the input string
// $    matches the end of the input string
// *    matches zero or more occurrences of the previous character
int matchstar(int c, char *regexp, char *text) {
  do {
    if (matchhere(regexp, text))
      return 1;
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return 0;
}
int matchhere(char *regexp, char *text) {
  if (regexp[0] == '\0')
    return 1;
  if (regexp[1] == '*')
    return matchstar(regexp[0], regexp + 2, text);
  if (regexp[0] == '$' && regexp[1] == '\0')
    return *text == '\0';
  if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
    return matchhere(regexp + 1, text + 1);
  return 0;
}
int match(char *regexp, char *text) {
  if (regexp[0] == '^')
    return matchhere(regexp + 1, text);
  do {
    if (matchhere(regexp, text))
      return 1;
  } while (*text++ != '\0');
  return 0;
}

/* init.c */
#include "ucode.c"
void parent_loop();
extern int open();
extern char *strcpy(), *strcat();
int cnsl_pid, srl0_pid, srl1_pid;
int in, out;
int main(int argc, char const *argv[]) {
  int pid = getpid();
  in = open("/dev/tty0", O_RDONLY);
  out = open("/dev/tty0", O_WRONLY);
  puts("\n### INIT ###\n");
  cnsl_pid = fork();
  if (cnsl_pid) { // parent
    srl0_pid = fork();
    if (srl0_pid) { // parent
      srl1_pid = fork();
      if (srl1_pid) { // parent
        parent_loop();
      } else { // child
        exec("login /dev/ttyS1");
      }
    } else { // child
      exec("login /dev/ttyS0");
    }
  } else { // child
    exec("login /dev/tty0");
  }
  return 0;
}
void parent_loop() {
  while (1) {
    int child_pid, status;
    printf("P%d waits for dead children...\n", getpid());
    child_pid = wait(&status);
    printf("P%d harvests dead child P%d with status %x\n", getpid(), child_pid,
           status);
    if (child_pid == cnsl_pid || child_pid == srl0_pid ||
        child_pid == srl1_pid) {
      int new_child = fork();
      if (new_child) { // parent
        printf("P%d forks login process P%d\n", getpid(), new_child);
      } else { // child
        if (child_pid == cnsl_pid) {
          cnsl_pid = new_child;
          exec("login /dev/tty0");
        } else if (child_pid == srl0_pid) {
          srl0_pid = new_child;
          exec("login /dev/ttyS0");
        } else if (child_pid == srl1_pid) {
          srl1_pid = new_child;
          exec("login /dev/ttyS1");
        }
      }
    }
  }
}

/* l2u.c */
#include "ucode.c"
#define PROG_NAME "L2U"
int fd1, fd2;
void setup(int argc, char *argv[]) {
  if (argc == 1) {
    fd1 = STDIN;
    fd2 = STDOUT;
  } else if (argc == 2) {
    fd1 = open(argv[1], O_RDONLY);
    fd2 = STDOUT;
  } else {
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_WRONLY | O_CREAT);
  }
  if (fd1 < 0 || fd2 < 0) {
    printf("%s: fail to open file.\n", PROG_NAME);
    exit(1);
  }
}
int main(int argc, char *argv[]) {
  char buf[256];
  int n;
  setup(argc, argv);
  while (n = read(fd1, buf, 256)) {
    buf[n] = 0;
    for (int i = 0; i < 256; i++) {
      if (buf[i] > 96 && buf[i] < 123)
        buf[i] -= 32;
    }
    write(fd2, buf, n);
  }
  exit(0);
}

/* login.c */
#include "ucode.c"
#define PSWRD_PATH "/etc/passwd"

extern int atoi();
int authenticate();
char **split(char *src, char *tokens[], char delim);

int in, out, err, fd;
char uname[128], home[128], program[128];
int uid, gid;

int main(int argc, char const *argv[]) {
  char *dev = (char *)argv[1];
  close(STDIN), close(STDOUT);
  open(dev, STDIN);
  open(dev, STDOUT);
  open(dev, STDERR);
  settty(dev);

  if (argc != 2) {
    printf("\nLOGIN: wrong number of args\n");
    exit(1);
  }

  char user[128], pass[128];
  for (int tries = 3; tries >= 0; tries--) {
    printf("Login: ");
    gets(user);
    printf("Password: ");
    gets(pass);

    if (authenticate(user, pass) == 1) {
      printf("Welcome %s!\n", uname);
      chuid(uid, gid);
      chdir(home);
      exec(program);
      break;
    }

    printf("%d login attempts remaining.\n", tries);
  }
  printf("too many attempts, goodbye");
  close(fd);
  return 0;
}

int authenticate(char *user, char *pass) {
  fd = open(PSWRD_PATH, O_RDONLY);

  if (fd == '\0') {
    printf("LOGIN: fail to open %s\n", PSWRD_PATH);
    return 0;
  }
  char buf[512];
  int amt_read = read(fd, buf, 512);
  if (amt_read <= 0) {
    printf("LOGIN: fail to read %s\n", PSWRD_PATH);
    return 0;
  }
  char *lines[16], *fields[8];
  split(buf, lines, '\n');
  for (int i = 0; lines[i]; i++) {
    split(lines[i], fields, ':');
    if (!strcmp(fields[0], user) && !strcmp(fields[1], pass)) {
      puts("good login\n");
      gid = atoi(fields[2]);
      uid = atoi(fields[3]);
      strcpy(uname, fields[4]);
      strcpy(home, fields[5]);
      strcpy(program, fields[6]);
      close(fd);
      return 1;
    }
  }
  puts("bad login\n");
  close(fd);
  return 0;
}

/* ls.c */
#include "ucode.c"
/*
LS NOT WORKING, RAN OUT OF TIME
        ¯\_(ツ)_/¯
*/
char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";
struct stat mystat, *sp;
int opendir(pathaname) { return open(pathname, O_RDONLY); }
int ls_file(char *fname) {
  struct stat fstat, *sp = &fstat;
  int r, i;
  char sbuf[4096], ftime[4096];
  r = stat(fname, sp);
  if (S_ISDIR(sp->st_mode))
    printf("%c", 'd');
  if (S_ISREG(sp->st_mode))
    printf("%c", '-');
  if (S_ISLNK(sp->st_mode))
    printf("%c", 'l');
  for (i = 8; i >= 0; i--) {
    if (sp->st_mode & (1 << i))
      printf("%c", t1[i]);
    else
      printf("%c", t2[i]);
  }
  printf("%4d ", sp->st_nlink);
  printf("%4d ", sp->st_uid);
  printf("%8d ", sp->st_size);
  printf("%s", fname);
  if (S_ISLNK(sp->st_mode)) {
    r = readlink(fname, sbuf);
    printf(" -> %s", sbuf);
  }
  printf("\n");
}
int ls_dir(char *dname) {
  char name[256];
  DIR *dp, *ep;
  dp = opendir(dname);
  while (ep = readdir(dp)) {
    strcpy(name, ep->name);
    if (!strcmp(name, ".") || !strcmp(name, ".."))
      continue;
    strcpy(name, dname);
    strcat(name, "/");
    strcat(name, ep->name);
    ls_file(name);
  }
}
int main(int argc, char *argv[]) {
  struct stat mystat, *sp;
  int r;
  char *s;
  char filename[1024], cwd[1024];
  s = argv[1];
  if (argc == 1)
    s = "./";
  sp = &mystat;
  if ((r = stat(s, sp)) < 0) {
    exit(1);
  }
  strcpy(filename, s);
  if (s[0] != '/') {
    getcwd(cwd);
    strcpy(filename, cwd);
    strcat(filename, "/");
    strcat(filename, s);
  }
  if (S_ISDIR(sp->st_mode))
    ls_dir(filename);
  else
    ls_file(filename);
}

/* more.c */
#include "ucode.c"
void print_line();
void print_page();
#define PROG_NAME "MORE"
int fd, fd_tty;
char buf[256];
void setup(int argc, char *argv[]) {
  if (argc == 1)
    fd = STDIN;
  else if (argc == 2) {
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
      printf("%s: fail to open %s \n", PROG_NAME, argv[1]);
      exit(1);
    }
  } else if (argc > 3) {
    printf("%s: too many args\n", PROG_NAME);
    exit(1);
  }
  gettty(buf);
  fd_tty = open(buf, O_RDONLY);
}
int main(int argc, char *argv[]) {
  char c = 0;
  setup(argc, argv);
  print_page(fd);
  while (c != 'q') {
    c = fgetc(fd_tty);
    switch (c) {
    case '\r':
      print_line(fd);
      break;
    case ' ':
      print_page(fd);
      break;
    case 'q':
      printf(" \n");
      break;
    }
  }
  exit(0);
}
// more print commands
void print_line(int fd) {
  char s[512];
  int n = readline(fd, s);
  if (n == 0 || !*s)
    exit(0);
  printf("%s", s);
}
void print_page(int fd) {
  for (int i; i < 20; i++)
    print_line(fd);
}

/* sh.c */
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
  // if pipe given then write to it
  if (pd_in) {
    close(pd_in[0]);
    close(1);
    dup(pd_in[1]);
    close(pd_in[1]);
  }
  // pop last command
  char *tail = pop_tail(line);
  int pd_out[2], pid;
  if (tail) {
    pipe(pd_out);
    pid = fork();
    // if parent then read from it
    if (pid) { // parent
      close(pd_out[1]);
      close(0);
      dup(pd_out[0]);
      close(pd_out[0]);
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
  trimws(&cmd);
  redirect_io(cmd);
  exec(cmd);
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

/* ucode.c changes */
// Only changes to ucode.c are shown
char **split(char *src, char *tokens[], char delim) {
  // Modifies src!
  // Null terminates tokens
  int index = 1;
  tokens[0] = src;
  for (; *src != 0; src++) {
    if (*src == delim) {
      *src = 0;
      tokens[index++] = src + 1;
    }
  }
  tokens[index] = 0;
  return tokens;
}
int fgetc(int fd) {
  int c, n;
  n = read(fd, (char *)&c, 1);
  if (n == 0 || c == 4 || c == 0)
    return EOF;
  return (c & 0x7F);
}
int readline(int fd, char *s) {
  int c;
  char *cp = s;
  c = fgetc(fd);
  while ((c != EOF) && (c != '\r') && (c != '\n')) {
    *cp++ = c;
    c = fgetc(fd);
  }
  if (c == EOF)
    return 0;
  *cp++ = c;
  *cp = 0;
  return strlen(s);
}
char *trimws(char **strp) {
  char *str;
  for (str = *strp; *str; str++)
    ;
  str--;
  for (; *str == ' '; str--)
    *str = 0;
  for (str = *strp; *str == ' '; str++)
    ;
  *strp = str;
  return str;
}

/* uio.c changes */
// Only changes to uio.c are shown
#define __S_IFMT 0170000 /* These bits determine file type.  */
#define __S_ISTYPE(mode, mask) (((mode)&__S_IFMT) == (mask))
#define __S_IFDIR 0040000 /* Directory.  */
#define S_ISDIR(mode) __S_ISTYPE((mode), __S_IFDIR)
#define __S_IFREG 0100000 /* Regular file.  */
#define S_ISREG(mode) __S_ISTYPE((mode), __S_IFREG)
#define __S_IFLNK 0120000 /* Symbolic link.  */
#define S_ISLNK(mode) __S_ISTYPE((mode), __S_IFLNK)

int puts(const char *s) { return printf("%s", s); }
