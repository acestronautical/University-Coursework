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
