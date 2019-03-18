#include "file_man.h"
#include "util.c"

int mount_root(char *rootdev) {
  int i;
  MTABLE *mp;
  super_block *sp;
  group_desc *gp;
  char buf[BLKSIZE];
  dev = open(rootdev, O_RDWR);
  if (dev < 0) {
    printf("panic : can’t open root device\n");
    exit(1);
  }
  /* get super block of rootdev */
  get_block(dev, 1, buf);
  sp = (super_block *)buf;
  /* check magic number */
  if (sp->s_magic != SUPER_BLOCK_MAGIC) {
    printf("super magic=%x : %s is not an EXT2 filesys\n", sp->s_magic,
           rootdev);
    exit(0);
  }
  // fill mount table mtable[0] with rootdev information
  mp = &mtable[0];
  // use mtable[0]
  mp->dev = dev;
  // copy super block info into mtable[0]
  ninode = mp->ninodes = sp->s_inodes_count;
  nblocks = mp->nblocks = sp->s_blocks_count;
  strcpy(mp->devName, rootdev);
  strcpy(mp->mntName, "/");
  get_block(dev, 2, buf);
  gp = (group_desc *)buf;
  bmap = mp->bmap = gp->bg_block_bitmap;
  imap = mp->imap = gp->bg_inode_bitmap;
  iblock = mp->iblock = gp->bg_inode_table;
  printf("bmap=%d imap=%d iblock=%d\n", bmap, imap, iblock);
  // call iget(), which inc minode’s refCount
  root = iget(dev, 2);
  // get root inode
  mp->mntDirPtr = root;
  // double link
  root->mntPtr = mp;
  // set proc CWDs
  for (i = 0; i < NPROC; i++)
    // set proc’s CWD
    proc[i].cwd = iget(dev, 2); // each inc refCount by 1
  printf("mount : %s mounted on / \n", rootdev);
  return 0;
}