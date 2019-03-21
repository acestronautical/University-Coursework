#include "fs.h"

int mount_root(char *dev_path) {
  int i;

  mount_entry *me;
  super_block *sb;
  group_desc *gd;
  char buf[BLKSIZE];
  int dev = open(dev_path, O_RDWR);
  if (dev < 0) {
    printf("panic : can’t open root device\n");
    exit(1);
  }
  /* get super block of device */
  get_block(dev, 1, buf);
  sb = (super_block *)buf;
  /* check magic number */
  if (sb->s_magic != EXT2_SUPER_MAGIC) {
    printf("super magic=%x : %s is not an EXT2 filesys\n", sb->s_magic,
           dev_path);
    exit(0);
  }
  // fill mount table mtable_arr[0] with device information
  me = &mount_entry_arr[0];
  // use mtable[0]
  me->dev_fd = dev;
  // copy super block info into mtable_arr[0]
  me->ninodes = sb->s_inodes_count;
  me->nblocks = sb->s_blocks_count;
  strcpy(me->dev_name, dev_path);
  strcpy(me->mnt_name, "/");
  get_block(dev, 2, buf);
  gd = (group_desc *)buf;
  me->bmap = gd->bg_block_bitmap;
  me->imap = gd->bg_inode_bitmap;
  me->iblock = gd->bg_inode_table;
  printf("bmap=%d imap=%d iblock=%d\n", me->bmap, me->imap, me->iblock);
  // call get_inode(), which inc minode’s refCount
  root_inode = get_inode(dev, 2);
  // get root inode
  me->mnt_dir_ptr = root_inode;
  // double link
  root_inode->mntPtr = me;
  // set proc CWDs
  for (i = 0; i < NUM_PROCS; i++)
    // set proc’s CWD
    proc_arr[i].cwd = get_inode(dev, 2); // each inc refCount by 1
  printf("mount : %s mounted on / \n", dev_path);
  return 0;
}
