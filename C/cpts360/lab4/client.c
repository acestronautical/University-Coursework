// The echo client client.c
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 256
// Define variables
struct hostent *hp;
struct sockaddr_in server_addr;
typedef struct cmd {
  char *argv[64];
  int argc;
} cmd;
int server_sock, r;
int SERVER_IP, SERVER_PORT;
// clinet initialization code
int client_init(char *argv[]) {
  printf("CONNECTING\n");
  printf("--getting server info\n");
  hp = gethostbyname(argv[1]);
  if (!hp) {
    printf("unknown host %s\n", argv[1]);
    exit(1);
  }
  SERVER_IP = *(long *)hp->h_addr_list[0];
  SERVER_PORT = atoi(argv[2]);
  printf("--creating TCP socket\n");
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0) {
    printf("socket call failed\n");
    exit(2);
  }
  printf("--filling server_addr with server's IP and PORT#\n");
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = SERVER_IP;
  server_addr.sin_port = htons(SERVER_PORT);
  // Connect to server
  printf("--connecting to server ....\n");
  r = connect(server_sock, (struct sockaddr *)&server_addr,
              sizeof(server_addr));
  if (r < 0) {
    printf("connect failed\n");
    exit(1);
  }
  printf("--hostname=%s  IP=%s  PORT=%d\n", hp->h_name,
         inet_ntoa((struct in_addr){SERVER_IP}), SERVER_PORT);
  printf("--connection to %s success\n", hp->h_name);
  printf("CONNECTED\n");
  return 0;
}
int do_lcat(cmd *c) {
  int fd, m = 0, n;
  char buf[MAX];
  fd = STDIN_FILENO; // default to stdin
  if (c->argc > 1)
    fd = open(c->argv[1], O_RDONLY);
  if (fd < 0)
    exit(1);
  while ((n = read(fd, buf, MAX)))
    m += write(STDOUT_FILENO, buf, n);
  return m;
}
int do_lls(cmd *c) { return 0; }
int do_lcd(cmd *c) {
  if (c->argc > 1)
    chdir(c->argv[1]);
  else
    chdir(getenv("HOME"));
  char cwd[64];
  getcwd(cwd, sizeof(cwd));
  printf("cd to %s\n OKFINEWHATEVER\n", cwd);
  return 0;
}
int do_lpwd(cmd *c) {
  char cwd[64];
  getcwd(cwd, sizeof(cwd));
  printf("pwd: %s\n ALRIGHTALRIGHTALRIGHT\n", cwd);
  return 0;
}
int do_lmkdir(cmd *c) { return 0; }
int do_lrmdir(cmd *c) { return 0; }
int do_lrm(cmd *c) { return 0; }
int do_quit(cmd *c) { exit(0); }
int do_cmd(cmd *c) {
  char resp[MAX];
  if (!strcmp(c->argv[0], "pwd")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "ls")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "cd")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "mkdir")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "rmdir")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "rm")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "get")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "put")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "lcat")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "lls")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "lcd")) {
    do_lcd(c);
  } else if (!strcmp(c->argv[0], "lpwd")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "lmkdir")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "lrmdir")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "lrm")) {
    read(server_sock, resp, MAX);
    puts(resp);
  } else if (!strcmp(c->argv[0], "quit")) {
    exit(0);
  } else {
    puts("Bad command");
  }
  return 0;
}
int parse_input(char *line, cmd *c) {
  // split by whitespace into cmd struct
  int i = 0;
  char *s = strtok(line, " \t");
  for (; s; i++) {
    c->argv[i] = s;
    s = strtok(NULL, " \t");
  }
  c->argc = i;
  c->argv[i] = NULL;
  return i;
}
int main(int argc, char *argv[]) {
  int n;
  char line[MAX];
  if (argc < 3) {
    printf("Usage : client ServerName SeverPort\n");
    exit(1);
  }
  client_init(argv);
  // sock <---> server
  while (1) {
    printf("----------------------------------------\n"
           "get  put ls  cd   pwd    mkdir  rmdir rm\n"
           "lcat lls lcd lpwd lmkdir lrmdir lrm quit\n"
           "----------------------------------------\n");
    printf("@%s: ", hp->h_name);
    // get user input
    bzero(line, MAX);           // zero out line[ ]
    fgets(line, MAX, stdin);    // get a line (end with \n) from stdin
    line[strlen(line) - 1] = 0; // kill \n at end
    if (!line[0])               // exit if NULL line
      exit(1);
    // write command
    n = write(server_sock, line, MAX);
    // do command
    cmd c;
    parse_input(line, &c);
    do_cmd(&c);
  }
  return 0;
}