typedef struct cmd {
  int argc;
  char argv[64];
} cmd;

// specific commands
int do_cd(cmd);
int do_chmod(cmd);
int do_creat(cmd);
int do_link(cmd);
int do_ls(cmd);
int do_mkdir(cmd);
int do_pwd(cmd);
int do_rmdir(cmd);
int do_stat(cmd);
int do_symlink(cmd);
int do_touch(cmd);
int do_unlink(cmd);

// utility
int spawn_proc(int, int, cmd *);