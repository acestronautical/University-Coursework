// The echo client client.c
#include <arpa/inet.h>
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

int server_sock, r;
int SERVER_IP, SERVER_PORT;

// clinet initialization code
int client_init(char *argv[]) {
  printf("CONNECTING\n");
  printf("--getting server info\n");
  hp = gethostbyname(argv[1]);
  if (hp == 0) {
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

int main(int argc, char *argv[]) {
  int n;
  char line[MAX], ans[MAX];

  if (argc < 3) {
    printf("Usage : client ServerName SeverPort\n");
    exit(1);
  }

  client_init(argv);
  // sock <---> server

  while (1) {
    printf("input a line : ");
    bzero(line, MAX);        // zero out line[ ]
    fgets(line, MAX, stdin); // get a line (end with \n) from stdin

    line[strlen(line) - 1] = 0; // kill \n at end
    if (line[0] == 0)           // exit if NULL line
      exit(0);

    // write
    n = write(server_sock, line, MAX);
    // read
    n = read(server_sock, ans, MAX);
  }
  return 0;
}