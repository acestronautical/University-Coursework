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