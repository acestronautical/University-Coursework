#include "lab2.h"

int main(int argc, char const *argv[]) {
  // initialize globals
  cwd = root = &(node){
      .name = "/", .type = DIR, .child = NULL, .sibling = NULL, .parent = NULL};

  // vars
  char userInput[128], commandName[16], pathName[64], cwdName[64] = "/";
  int (*commandPtr)(char *);

  // run
  loop {
    printf("\nfileSim:");
    pwd(NULL);
    printf("$");

    // get user input line = [command pathName];
    fgets(userInput, 128, stdin);
    userInput[strlen(userInput) - 1] = '\0';
    pathName[0] = '\0';
    if (sscanf(userInput, "%s %s", commandName, pathName) < 1)
      continue;

    // identify the command;
    if (commandPtr = findCmd(commandName))
      if (commandPtr(pathName) != EXIT_SUCCESS)
        printf("command failed");
  }
}
