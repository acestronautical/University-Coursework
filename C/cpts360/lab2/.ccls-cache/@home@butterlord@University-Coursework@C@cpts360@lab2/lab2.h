#pragma once
#include <ctype.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DIR 'D'
#define _FILE 'F'
#define loop while (1)

// types
typedef struct node {
  char name[64];
  char type;
  struct node *child, *sibling, *parent;
} node;

typedef int (*cmdFunction)(char *);

// fileSim Prototypes
int mkdir(char *pathName);
int rmdir(char *pathName);
int cd(char *pathName);
int ls(char *pathName);
int pwd(char *pathName);
int creat(char *pathName);
int rm(char *pathName);
int save(char *pathName);
int reload(char *pathName);
int menu(char *pathName);
int quit(char *pathName);
cmdFunction findCmd(char *command);
// globals
node *root, *cwd;