#include "fs/fs.h"

int main(int argc, char const *argv[]) {
  char line[128], cmd[16], pathname[64];
  char *rootdev;
  if (argc > 1)
    rootdev = (char *)argv[1];
  fs_init();
  mount_root(rootdev);
  while (1) {
    printf("P%d running: ", running->pid);
    printf("input command : ");
    fgets(line, 128, stdin);
    line[strlen(line) - 1] = 0;
    if (!line[0])
      continue;
    sscanf(line, "%s %s", cmd, pathname);
    printf("ECHO: cmd=%s pathnam=%s\n", cmd, pathname);
  }
}