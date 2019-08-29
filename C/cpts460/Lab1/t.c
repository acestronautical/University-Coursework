/*******************************************************
 *                  @t.c file                          *
 *******************************************************/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define TRK 18
#define CYL 36
#define BLK 1024

#include "ext2.h"
typedef struct ext2_group_desc GD;
typedef struct ext2_inode INODE;
typedef struct ext2_dir_entry_2 DIR;

int prints(char *s) {
  while (*s) 
    putc(*s++);
}

// int gets(char *s) {
//   while (*s = getc() != '\r')
//     putc(*s++);
//   *s = '\0';
//   putc('\r'), putc('\n');
// }

// don't know what this is for
u16 NSEC = 2; 
// Block buffers
char buf1[BLK], buf2[BLK];

int getblk(u16 blk, char *buf) {
  readfd((2 * blk) / CYL, ((2 * blk) % CYL) / TRK, ((2 * blk) % CYL) % TRK,
         buf);
}

// u8 streq(char *s1, char *s2) {
//   while (*s1 && *s2 && *s1 == *s2)
//     s1++, s2++;
//   return *s1 == *s2;
// }

u16 search(INODE *ip, char *name) {
  char c, i;
  DIR *dp;
  // for each direct block
  for (i = 0; i < 12; i++) {
    // if block is zero error
    if ((u16)ip->i_block[i] == 0)
      error();
    // read block into buf2
    getblk((u16)ip->i_block[i], buf2);
    dp = (DIR *)buf2;
    // for each dir to end of block
    while ((char *)dp < buf2 + BLK) {
      // null terminate dp->name
      c = dp->name[dp->name_len];
      dp->name[dp->name_len] = '\0';
      prints(dp->name), putc(' ');
      if (!strcmp(name, dp->name)) {
        dp->name[dp->name_len] = c;
        prints("\r\n");
        return (u16)dp->inode;
      }
      // restore overwritten char
      dp->name[dp->name_len] = c;
      // go to next dir
      dp = (char *)dp + dp->rec_len;
    }
  }
  // error if not found
  error();
}

main() {
  INODE *inode_p;
  GD *gd_p;
  u16 iblk, ino, i;
  u32 *bp;
  char *name[2];
  name[0] = "boot", name[1] = "mtx";
  // read group descriptor
  getblk(2, buf1);
  gd_p = (GD *)buf1;
  // get inode start block from gd
  iblk = (u16)gd_p->bg_inode_table;
  // get inode of root
  getblk(iblk, buf1);
  inode_p = (INODE *)buf1 + 1;
  // search boot then mtx
  for (i = 0; i < 2; i++) {
    ino = search(inode_p, name[i]) - 1;
    getblk(iblk + (ino / 8), buf1);
    inode_p = (INODE *)buf1 + (ino % 8);
  }
  // read indirect block of mtx into buf2
  getblk((u16)inode_p->i_block[12], buf2);
  // set bios base address
  setes(0x1000);
  // copy direct blocks
  for (i = 0; i < 12; i++) {
    getblk((u16)inode_p->i_block[i], 0);
    inces(), putc('A');
  }
  // copy indirect blocks
  bp = (u32 *)buf2;
  while (*bp) {
    getblk((u16)*bp++, 0);
    inces(), putc('H');
  }
  prints("!!!\r\n?"), getc();
}
