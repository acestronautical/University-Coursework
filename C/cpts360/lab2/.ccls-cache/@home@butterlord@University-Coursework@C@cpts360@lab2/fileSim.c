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
  if (!path || !*path)
    return NULL;
  node *cur = cwd;
  if (*path == '/')
    cur = root;
  char *s = strtok(path, "/");
  if (s) {
    if (!strcmp(s, ".")) {
      cur = cwd;
      s = strtok(0, "/");
    } else if (!strcmp(s, "..")) {
      cur = cwd->parent;
      s = strtok(0, "/");
    }
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
  if (!target || target->type != _DIR)
    return NULL;
  return target;
}

node *searchFile(char *fileName) {
  node *target = searchNode(fileName);
  if (!target || target->type != _FILE)
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

  if (!(n->type == _DIR) || !(n->type == _FILE))
    n->type == _FILE;
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
  new->type = _DIR;
  return insertNode(pathName, new);
}

int rmdir(char *pathName) {
  node *target = searchDir(pathName);
  if (!target || target->type != _DIR)
    return EXIT_FAILURE;
  return deleteNode(target);
}

int cd(char *pathName) {
  if (!pathName || !*pathName) {
    cwd = root;
    return EXIT_SUCCESS;
  }
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

char *pwdRecursive(node *cur, char *buf) {
  if (!cur->parent)
    return strcat(buf, cur->name);
  pwdRecursive(cur->parent, buf);
  strcat(buf, cur->name);
  strcat(buf, "/");
  return buf;
}

int pwd(char *pathName) {
  node *cur = cwd;
  char buf[128] = {'\0'};
  return !printf("%s", pwdRecursive(cur, buf));
}

int creat(char *pathName) {
  node *new = (node *)malloc(sizeof(node));
  new->type = _FILE;
  return insertNode(pathName, new);
  return EXIT_SUCCESS;
}

int rm(char *pathName) {
  node *target = searchFile(pathName);
  if (!target || target->type != _FILE)
    return EXIT_FAILURE;
  return deleteNode(target);
}
int saveRecursive(node *cur, FILE *fp) {
  char buf[128] = {'\0'};
  if (!cur)
    return EXIT_FAILURE;
  fprintf(fp, "%c %s\n", cur->type, pwdRecursive(cur, buf));
  saveRecursive(cur->child, fp);
  saveRecursive(cur->sibling, fp);
  return EXIT_SUCCESS;
}

int save(char *pathName) {
  FILE *fp = fopen(pathName, "w+");
  if (!fp)
    return EXIT_FAILURE;
  saveRecursive(root, fp);
  fclose(fp);
  return EXIT_SUCCESS;
}

int reload(char *pathName) {
  char line[128], type[2], path[128];
  FILE *fp = fopen(pathName, "r");
  if (!fp)
    return EXIT_FAILURE;
  while (!feof(fp)) {
    fgets(line, 128, fp);
    sscanf(line, "%s %s", type, path);
    if (*type == _DIR)
      mkdir(path);
    else if (*type == _FILE)
      creat(path);
  }
  fclose(fp);
  return EXIT_SUCCESS;
}

int menu(char *pathName) {
  printf("mkdir pathname  :make a new directory for a given pathname\n"
         "rmdir pathname  :remove the directory, if it is empty.\n"
         "cd [pathname]   :change CWD to pathname, or to / if no pathname.\n"
         "ls [pathname]   :list the directory contents of pathname or CWD\n"
         "pwd             :print the (absolute) pathname of CWD\n"
         "creat pathname  :create a _FILE node.\n"
         "rm pathname     :remove the _FILE node.\n"
         "save filename   :save the current file system tree as a file\n"
         "reload filename :construct a file system tree from a file\n"
         "menu            : show a menu of valid commands\n"
         "quit            : save the file system tree, then terminate the "
         "program.\n");
  return EXIT_SUCCESS;
}

int quit(char *pathName) {
  save("autosave");
  exit(EXIT_SUCCESS);
}

// string to command
cmdFunction findCmd(char *command) {

  const char *cmdNames[] = {"mkdir", "rmdir",  "ls",   "cd",   "pwd",  "creat",
                            "rm",    "reload", "save", "menu", "quit", NULL};

  const int (*cmdPtrs[])(char *) = {
      (int (*)())mkdir, rmdir, ls,   cd,  pwd, creat, rm,
      reload,           save,  menu, quit};

  for (int i = 0; cmdNames[i]; i++) {
    if (!strcmp(command, cmdNames[i]))
      return cmdPtrs[i];
  }
  return NULL;
}
