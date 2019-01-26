#include "lab2.h"

// utility
char *safeDirname(char *pathName, char *buf) {
  strcpy(buf, pathName);
  return strcpy(buf, dirname(buf));
}

char *safeBasename(char *pathName, char *buf) {
  strcpy(buf, pathName);
  return strcpy(buf, basename(buf));
}

// search
node *searchNode(char *path) {
  node *cur = root;
  char *s = strtok(path, "/");
  if (!strcmp(s, ".")) {
    cur = cwd;
    s = strtok(0, "/");
  } else if (!strcmp(s, "..")) {
    cur = cwd->parent;
    s = strtok(0, "/");
  }
  while (s) {
    cur = cur->child;
    while (cur && strcmp(cur->name, s))
      cur = cur->sibling;
    if (!cur)
      return NULL;
    s = strtok(0, "/");
  }
  return cur;
}

node *searchDir(char *dirName) {
  node *target = searchNode(dirName);
  if (!target || target->type != DIR)
    return NULL;
  return target;
}

node *searchFile(char *fileName) {
  node *target = searchNode(fileName);
  if (!target || target->type != FILE)
    return NULL;
  return target;
}

// insert
int insertNode(char *pathName, node *n) {
  if (!pathName || !*pathName)
    return EXIT_FAILURE;

  char dirName[128];
  safeDirname(pathName, dirName);
  char baseName[64];
  safeBasename(pathName, baseName);

  if (searchDir(pathName))
    return EXIT_FAILURE;

  node *parentDir = searchDir(dirName);
  if (!parentDir)
    return EXIT_FAILURE;

  if (!(n->type == DIR) || !(n->type == FILE))
    n->type == FILE;
  n->parent = parentDir;
  strcpy(n->name, baseName);

  if (!parentDir->child)
    parentDir->child = n;
  else {
    node *cur = parentDir->child;
    while (cur->sibling)
      cur = cur->sibling;
    cur->sibling = n;
  }
  return EXIT_SUCCESS;
}

// delete
int deleteNode(node *target) {
  if (!target || !target->parent || target->child)
    return EXIT_FAILURE;
  node *cur = target->parent->child;
  if (cur == target)
    target->parent->child = target->sibling;
  else {
    node *prev = cur;
    while (!(cur == target)) {
      prev = cur;
      cur = cur->sibling;
    }
    prev->sibling = cur->sibling;
  }
  free(cur);
  return EXIT_SUCCESS;
}

// commands
int mkdir(char *pathName) {
  node *new = (node *)malloc(sizeof(node));
  new->type = DIR;
  return insertNode(pathName, new);
}

int rmdir(char *pathName) {
  node *target = searchDir(pathName);
  if (!target || target->type != DIR)
    return EXIT_FAILURE;
  return deleteNode(target);
}

int cd(char *pathName) {
  node *cur = searchDir(pathName);
  if (!cur)
    return EXIT_FAILURE;
  cwd = cur;
  return EXIT_SUCCESS;
}

int ls(char *pathName) {
  node *cur;
  if (!*pathName)
    cur = cwd;
  else
    cur = searchDir(pathName);
  if (!cur)
    return EXIT_FAILURE;
  cur = cur->child;
  for (; cur; cur = cur->sibling)
    printf("%c:%s ", cur->type, cur->name);
  return EXIT_SUCCESS;
}

int pwdRecursive(node *cur) {
  if (!cur->parent)
    return printf("%s", cur->name) == 1;
  pwdRecursive(cur->parent);
  printf("%s/", cur->name);
}

int pwd(char *pathName) {
  node *cur = cwd;
  char buf[128];
  if (pwdRecursive(cur))
    return EXIT_SUCCESS;
  return EXIT_FAILURE;
}

int creat(char *pathName) {
  node *new = (node *)malloc(sizeof(node));
  new->type = FILE;
  return insertNode(pathName, new);
  return EXIT_SUCCESS;
}

int rm(char *pathName) {
  node *target = searchDir(pathName);
  if (!target || target->type != FILE)
    return EXIT_FAILURE;
  return deleteNode(target);
}

int save(char *pathName) { return EXIT_SUCCESS; }

int reload(char *pathName) { return EXIT_SUCCESS; }

int menu(char *pathName) {
  printf("mkdir pathname  :make a new directory for a given pathname\n"
         "rmdir pathname  :remove the directory, if it is empty.\n"
         "cd [pathname]   :change CWD to pathname, or to / if no pathname.\n"
         "ls [pathname]   :list the directory contents of pathname or CWD\n"
         "pwd             :print the (absolute) pathname of CWD\n"
         "creat pathname  :create a FILE node.\n"
         "rm pathname     :remove the FILE node.\n"
         "save filename   :save the current file system tree as a file\n"
         "reload filename :construct a file system tree from a file\n"
         "menu            : show a menu of valid commands\n"
         "quit            : save the file system tree, then terminate the "
         "program.\n");
  return EXIT_SUCCESS;
}

int quit(char *pathName) {
  save(NULL);
  exit(EXIT_SUCCESS);
}

// string to command
cmdFunction findCmd(char *command) {

  const char *cmdNames[] = {"mkdir", "rmdir",  "ls",   "cd",   "pwd",  "creat",
                            "rm",    "reload", "save", "menu", "quit", NULL};

  const int (*cmdPtrs[])(char *) = {
      (int (*)())mkdir, rmdir, ls,  cd, pwd, creat, rm, save,
      reload,           menu,  quit};

  for (int i = 0; cmdNames[i]; i++) {
    if (!strcmp(command, cmdNames[i]))
      return cmdPtrs[i];
  }
  return NULL;
}
