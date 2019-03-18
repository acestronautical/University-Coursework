#include "file_man.h"
#include "./cmd/cmd.h"
#include "string.h"

int run_file_manager(int argc, char const *argv[]) {
  char line[128], cmd[16], pathname[64], *rootdev;
  if (argc > 1)
    rootdev = argv[1];
  fs_init();
  mount_root(rootdev);
  while (1) {
    printf("P%d running: ", running->pid);
    printf("input command : ");
    fgets(line, 128, stdin);
    line[strlen(line) - 1] = 0;
    if (line[0] == 0)
      continue;
    sscanf(line, "%s %s", cmd, pathname);
    if (!strcmp(cmd, "ls"))
      ls(pathname);
    if (!strcmp(cmd, "cd"))
      chdir(pathname);
    if (!strcmp(cmd, "pwd"))
      pwd(running->cwd);
    if (!strcmp(cmd, "quit"))
      quit();
  }
}
