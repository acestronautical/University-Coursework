#include <arpa/inet.h>
#include <dirent.h>
#include <libgen.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define MAX 256
// Define variables:
struct sockaddr_in server_addr, client_addr, name_addr;
struct hostent *hp;

// BEGIN LS STUFF
struct stat mystat, *sp;
char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";
// END LS STUFF
typedef struct cmd {
  char *argv[64];
  int argc;
} cmd;
int mysock,
    client_sock;  // socket descriptors
int serverPort;   // server port number
int r, length, n; // help variables
// Server initialization code:
int server_init(char *name) {
  printf("==================== server init ======================\n");
  // get DOT name and IP address of this host
  printf("1 : get and show server host info\n");
  hp = gethostbyname(name);
  if (!hp) {
    printf("unknown host\n");
    exit(1);
  }
  printf("    hostname=%s  IP=%s\n", hp->h_name,
         inet_ntoa((struct in_addr){(long)hp->h_addr_list[0]}));
  //  create a TCP socket by socket() syscall
  printf("2 : create a socket\n");
  mysock = socket(AF_INET, SOCK_STREAM, 0);
  if (mysock < 0) {
    printf("socket call failed\n");
    exit(2);
  }
  printf("3 : fill server_addr with host IP and PORT# info\n");
  // initialize the server_addr structure
  server_addr.sin_family = AF_INET;                // for TCP/IP
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // THIS HOST IP address
  server_addr.sin_port = 0;                        // let kernel assign port
  printf("4 : bind socket to host info\n");
  // bind syscall: bind the socket to server_addr info
  r = bind(mysock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (r < 0) {
    printf("bind failed\n");
    exit(3);
  }
  printf("5 : find out Kernel assigned PORT# and show it\n");
  // find out socket port number (assigned by kernel)
  length = sizeof(name_addr);
  r = getsockname(mysock, (struct sockaddr *)&name_addr, (socklen_t *)&length);
  if (r < 0) {
    printf("get socketname error\n");
    exit(4);
  }
  // show port number
  serverPort = ntohs(name_addr.sin_port); // convert to host ushort
  printf("    Port=%d\n", serverPort);
  // listen at port with a max. queue of 5 (waiting clients)
  printf("5 : server is listening ....\n");
  listen(mysock, 5);
  printf("===================== init done =======================\n");
  return 0;
}
int _pwd() {
  char cwd[256] = {0};
  getcwd(cwd, 256);
  write(client_sock, cwd, MAX);
  return 0;
}
int ls_file(char *fname) {
  struct stat fstat, *sp;
  int r, i;
  char ftime[64];
  sp = &fstat;
  if ((r = lstat(fname, &fstat)) < 0) {
    printf("can't stat %s\n", fname);
    exit(1);
  }
  if ((sp->st_mode & 0xF000) == 0x8000) // if (S_ISREG())
    printf("%c", '-');
  if ((sp->st_mode & 0xF000) == 0x4000) // if (S_ISDIR())
    printf("%c", 'd');
  if ((sp->st_mode & 0xF000) == 0xA000) // if (S_ISLNK())
    printf("%c", 'l');
  for (i = 8; i >= 0; i--) {
    if (sp->st_mode & (1 << i)) // print r|w|x
      printf("%c", t1[i]);
    else
      printf("%c", t2[i]);
    // or print -
  }
  printf("%4d ", (int)sp->st_nlink); // link count
  printf("%4d ", sp->st_gid);
  // gid
  printf("%4d ", sp->st_uid);
  // uid
  printf("%8d ", (int)sp->st_size);
  // file size
  // print time
  strcpy(ftime, ctime(&sp->st_ctime)); // print time in calendar form
  ftime[strlen(ftime) - 1] = 0;
  // kill \n at end
  printf("%s ", ftime);
  // print name
  printf("%s", basename(fname)); // print file basename
  // print -> linkname if symbolic file
  if ((sp->st_mode & 0xF000) == 0xA000) {
    // use readlink() to read linkname
    char linkname[256] = {0};
    readlink(fname, linkname, 256);
    printf(" -> %s", linkname); // print linked name
  }
  printf("\n");
  return 0;
}
int ls_dir(char *dname) {
  // use opendir(), readdir(); then call ls_file(name)
  return 0;
}
int ls(int argc, char *argv[]) {
  struct stat mystat, *sp = &mystat;
  int r;
  char *filename, path[1024], cwd[256];
  filename = "./";
  // default to CWD
  if (argc > 1)
    filename = argv[1]; // if specified a filename
  if ((r = lstat(filename, sp)) < 0) {
    printf("no such file %s\n", filename);
    exit(1);
  }
  strcpy(path, filename);
  if (path[0] != '/') { // filename is relative : get CWD path
    // 8 System Calls for File Operations
    getcwd(cwd, 256);
    strcpy(path, cwd);
    strcat(path, "/");
    strcat(path, filename);
  }
  if (S_ISDIR(sp->st_mode))
    ls_dir(path);
  else
    ls_file(path);
  return 0;
}
int do_cmd(cmd *c) {
  char resp[MAX];
  if (!strcmp(c->argv[0], "pwd")) {
    write(client_sock, "pwd OK", MAX);
  } else if (!strcmp(c->argv[0], "ls")) {
    ls(c->argc, c->argv);
    write(client_sock, "ls OK", MAX);
  } else if (!strcmp(c->argv[0], "cd")) {
    write(client_sock, "cd OK", MAX);
  } else if (!strcmp(c->argv[0], "mkdir")) {
    write(client_sock, "mkdir OK", MAX);
  } else if (!strcmp(c->argv[0], "rmdir")) {
    write(client_sock, "rmdir OK", MAX);
  } else if (!strcmp(c->argv[0], "rm")) {
    write(client_sock, "rm OK", MAX);
  } else if (!strcmp(c->argv[0], "get")) {
    write(client_sock, "get OK", MAX);
  } else if (!strcmp(c->argv[0], "put")) {
    write(client_sock, "put OK", MAX);
  } else if (!strcmp(c->argv[0], "quit")) {
    write(client_sock, "quit OK", MAX);
  } else {
    write(client_sock, "cmd FAIL", MAX);
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
  char *hostname;
  char line[MAX];
  if (argc < 2)
    hostname = "localhost";
  else
    hostname = argv[1];
  server_init(hostname);
  // Try to accept a client request
  while (1) {
    printf("server: accepting new connection ....\n");
    // Try to accept a client connection as descriptor newsock
    length = sizeof(client_addr);
    client_sock =
        accept(mysock, (struct sockaddr *)&client_addr, (socklen_t *)&length);
    if (client_sock < 0) {
      printf("server: accept error\n");
      exit(1);
    }
    printf("server: accepted a client connection from\n");
    printf("-----------------------------------------------\n");
    printf("        IP=%s  port=%d\n",
           inet_ntoa((struct in_addr){client_addr.sin_addr.s_addr}),
           ntohs(client_addr.sin_port));
    printf("-----------------------------------------------\n");
    // Processing loop: newsock <----> client
    while (1) {
      // read thing
      n = read(client_sock, line, MAX);
      if (!n) {
        printf("server: client died, server loops\n");
        close(client_sock);
        break;
      }
      // split by whitespace into cmd struct
      struct cmd *c;
      parse_input(line, c);
      // do command
      do_cmd(c);
    }
  }
  return 0;
}
