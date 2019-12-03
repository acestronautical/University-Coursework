#include "ucode.c"

char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";

int S_ISDIR(u16 mode) { return mode == 0b0100; }
int S_ISREG(u16 mode) { return mode == 0b1000; }
int S_ISLNK(u16 mode) { return mode == 0b1100; }
int opendir(char *pathname) { return open(pathname, O_RDONLY); }

int ls_file(char *fname) {
  struct stat fstat, *sp = &fstat;
  char sbuf[4096];
  stat(fname, sp);
  if (S_ISDIR(sp->st_mode))
    printf("%c ", 'd');
  if (S_ISREG(sp->st_mode))
    printf("%c ", '-');
  if (S_ISLNK(sp->st_mode))
    printf("%c ", 'l');
  for (int i = 8; i >= 0; i--) {
    if (sp->st_mode & (1 << i))
      printf("%c ", t1[i]); // print permission bit as r w x
    else
      printf("%c ", t2[i]); // print permission bit as -
  }
  printf("%d ", sp->st_nlink); // link count
  printf("%d ", sp->st_uid);   // uid
  printf("%d ", sp->st_size);  // file size
  printf("%s", fname);         // file basename

  if (S_ISLNK(sp->st_mode)) { // if symbolic link
    readlink(fname, sbuf);
    printf(" -> %s ", sbuf);
    // -> linked pathname
  }
  printf("\n ");
}

int ls_dir(char *dname) {
  char name[256];
  char *temp;
  // EXT2 filename: 1-255 chars
  DIR *dp;
  struct dirent *ep;

  // open DIR to read names
  dp = (DIR *)opendir(dname);
  while (ep = read((int)dp, temp, 128)) {
    // strcpy(name, ep->d_name);
    if (!strcmp(name, ".") || !strcmp(name, ".."))
      continue;
    // skip over . and .. entries
    // strcpy(name, dname);
    // strcat(name, "/");
    // strcat(name, ep->d_name);
    ls_file(name);
    // call list_file()
  }
}

int main(int argc, char *argv[]) {
  struct stat _stat, *sp = &_stat;
  char *path;
  char filename[1024], cwd[1024];

  path = argv[1];
  if (argc == 1)
    path = "./";

  if ((stat(path, sp)) < 0) { // stat() syscall
    printf("Could not stat %s\n", path);
    exit(1);
  }

  strcpy(filename, path);
  // if is relative to CWD
  if (path[0] != '/') {
    getcwd(cwd);
    strcpy(filename, cwd);
    strcat(filename, "/");
    strcat(filename, path);
  }
  if (S_ISDIR(sp->st_mode))
    ls_dir(filename); // list DIR
  else
    ls_file(filename); // list single file
}
