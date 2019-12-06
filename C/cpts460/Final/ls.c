#include "ucode.c"
/* 

MISSING READDIR SYSTEM CALL
NOT SURE HOW TO ACCOMPLISH LS WITHOUT IT

        ¯\_(ツ)_/¯
*/

char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";
struct stat mystat, *sp;
int opendir(pathaname) { return open(pathname, O_RDONLY); }
int ls_file(char *fname)
{
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

int ls_dir(char *dname)
{
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