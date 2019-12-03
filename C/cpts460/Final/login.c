#include "ucode.c"
#define PSWRD_PATH "/etc/passwd"

int authenticate();

int in, out, err;
char **split(char *src, char *tokens[], char delim);

char uname[128], home[128], program[128];
int uid, gid;

int main(int argc, char const *argv[]) {
  // Upon entry, argv[0]=login, argv[1]=/dev/ttyX
  if (argc != 2) {
    printf("\nLOGIN: wrong number of args\n");
    exit(1);
  }

  // close file descriptors inherited from INIT.
  // open argv[1] 3 times as in(0), out(1), err(2).
  char *dev = (char *)argv[1]; // discard const
  set_io(dev, &in, &out, &err);

  // set tty name string in PROC.tty
  settty(dev);

  char user[128], pass[128];
  for (int tries = 3; tries >= 0; tries--) {
    printf("Username: ");
    gets(user);
    printf("Password: ");
    gets(pass);

    // if user has a valid account
    if (authenticate(user, pass) == 1) {
      printf("Welcome %s!\n", uname);
      // change uid, gid to user's uid, gid
      chuid(uid, gid);
      // change cwd to user's home DIR
      chdir(home);
      // exec to program in user account // exec()
      exec(program);
      break;
    }

    printf("%d login attempts remaining.\n", tries);
  }
  printf("too many attempts, goodbye");
  exit(1);

  return 0;
}

int authenticate(char *user, char *pass) {
  // open /etc/passwd file for READ;
  int fp = open(PSWRD_PATH, O_RDONLY);
  if (fp == '\0') {
    printf("LOGIN: fail to open %s\n", PSWRD_PATH);
    return 0;
  }
  char buf[512];
  int amt_read = read(fp, buf, 512);
  if (amt_read <= 0) {
    printf("LOGIN: fail to read %s\n", PSWRD_PATH);
    return 0;
  }
  char *lines[16], *fields[8];
  split(buf, lines, '\n');
  for (int i = 0; lines[i]; i++) {
    // printf("line: %s\n", lines[i]);
    split(lines[i], fields, ':');
    if (!strcmp(fields[0], user) && !strcmp(fields[1], pass)) {
      puts("good login\n");
      gid = atoi(fields[2]);
      // printf("gid: %d\n", gid);
      uid = atoi(fields[3]);
      // printf("uid: %d\n", uid);
      strcpy(uname, fields[4]);
      // printf("uname: %s\n", uname);
      strcpy(home, fields[5]);
      // printf("home: %s\n", home);
      strcpy(program, fields[6]);
      // printf("program: %s\n", program);
      close(fp);
      return 1;
    }
  }

  puts("bad login\n");
  // close opened /etc/passwd file
  close(fp);
  return 0;
}

// Modifies src!
// Null terminates tokens1
char **split(char *src, char *tokens[], char delim) {
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