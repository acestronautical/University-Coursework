#ifndef MYSHELL
#define MYSHELL

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Types
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Globals
char cwd[1024];

char user_cmd[1024];
int cmdc;
char *cmdv[64];
char *user_name;
char *home_dir;
size_t bytes_read;
size_t bytes_wrote;

// Prototypes
int initShell();
int writePrompt();

int writeNewline();

int readCmd();
int doCmd();
int startShell();

#endif // MYSHELL