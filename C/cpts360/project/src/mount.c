#include "global.h"
#include "type.h"
#include "util.c"

int ninode, nblocks, bmap, imap, iblock;
int dev;
char gline[25], *name[16]; // tokenized component string strings
int nname;                 // number of component strings
char *rootdev = "mydisk";  // default root_device