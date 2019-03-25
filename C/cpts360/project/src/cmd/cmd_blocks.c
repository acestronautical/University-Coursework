#include "cmd.h"
bool do_blocks(cmd *c) {
  int i;
  char buf1[BLKSIZE_1024], buf2[BLKSIZE_1024], buf3[BLKSIZE_1024];
  int *fs_p1, *fs_p2, *fs_p3;
  path in_path;
  parse_path(c->argv[1], &in_path);
  minode m, *found_minode = &m;
  found_minode = search_path(&in_path);
  if (!found_minode)
    return false;
  inode *found_inode = &found_minode->inode;
  // do block stuff
  printf("direct blocks:\n");
  for (i = 0; i < 12; i++) {
    if (!found_inode->i_block[i])
      break;
    printf("%u\t", found_inode->i_block[i]);
  }
  printf("\n");

  printf("indirect blocks:\n");
  get_block(found_minode->dev, found_inode->i_block[12], buf1);
  if (found_inode->i_block[12])
    printf("[%u] :\n", found_inode->i_block[12]);
  fs_p1 = (int *)buf1;
  while (*fs_p1)
    printf("%u\t", *fs_p1++);
  printf("\n");

  printf("double indirect blocks:\n");
  get_block(found_minode->dev, found_inode->i_block[13], buf1);
  if (found_inode->i_block[13])
    printf("[%u] :\n", found_inode->i_block[13]);
  fs_p1 = (int *)buf1;
  while (*fs_p1) {
    get_block(found_minode->dev, *fs_p1, buf2);
    printf("[%u] :\n", *fs_p1);
    fs_p2 = (int *)buf2;
    while (*fs_p2)
      printf("%u\t", *fs_p2++);
    printf("\n");
    fs_p1++;
  }
  printf("\n");

  // printf("triple indirect blocks:\n");

  put_inode(found_minode);
  return true;
}