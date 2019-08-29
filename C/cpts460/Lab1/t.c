/*******************************************************
 *                  @t.c file                          *
 *******************************************************/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define TRK 18
#define CYL 36
#define BLK 1024

#include "./ext2.h"
typedef struct ext2_group_desc GD;
typedef struct ext2_inode INODE;
typedef struct ext2_dir_entry_2 DIR;

int prints(char *s) {
  while (*s) {
    if (*s == '\n')
      putc('\r');
  putc(*s++);
  }
}

int gets(char *s) {
  while (*s = getc() != '\r')
    putc(*s++);
  *s = '\0';
  putc('\r'), putc('\n');
}

u16 NSEC = 2;
u16 i, j;
char buf1[BLK], buf2[BLK];
u16 inode_table;

u16 getblk(u16 blk, char *buf) {
  readfd((2 * blk) / CYL, ((2 * blk) % CYL) / TRK, ((2 * blk) % CYL) % TRK,
         buf);
}

u8 streq(char *s1, char *s2) {
  while (*s1 && *s2 && *s1 == *s2)
    ;
  return *s1 == *s2;
}

strncpy(char *src, char *dest, u8 n) {
  for (i = 0; i < n && src[i]; i++)
    dest[i] = src[i];
  dest[++i] = '\0';
}

INODE* get_inode(int ino){
  u16 block, offset;
  block = (ino - 1) / 8 + inode_table;
  offset = (ino - 1) % 8;
  getblk(block, buf2);
  return (INODE*)buf2 + offset;
}

u16 search(INODE *ip, char *name) {
  // search direct blocks only
  char *buf1p;
  DIR *dp;
  for (i = 0; i < 12; i++) {
    // if direct block is null error
    if (!ip->i_block[i]){
      prints("null\n");
      error();
    }
    // get next direct block
    getblk((u16)ip->i_block[i], buf1);
    dp = (DIR *)buf1;
    buf1p = buf1;
    while (buf1p < buf1 + BLK) {
      strncpy(buf2, dp->name, dp->name_len);
      prints(buf2);
      prints("\n");
      if (streq(name, buf2))
        return dp->inode;
      buf1p += dp->rec_len;
      dp = (DIR *)buf1p;
    }
  }
  // error if not found
  prints("nf \n");
  error();
}

main() {
  INODE root_ino;
  prints("main start\n");
  getblk(2, buf1);
  inode_table = ((GD*)buf1)->bg_inode_table;
  root_ino = *(get_inode(2));
  prints("got root ino\n");
  // 1. Write YOUR C code to get the INODE of / boot / mtx INODE *ip-- > INODE
  i = search(&root_ino, "boot");
  prints("found boot\n");
  j = search(i, "mtximage");
  prints("found mtximage\n");
  // if INODE has indirect blocks
  // : get i_block[12] int buf2[]

  // 2. setes(0x1000); // MTX loading segment = 0x1000

  // 3. load 12 DIRECT blocks of INODE into memory beginning at segment 0x1000

  // 4. load INDIRECT blocks,
  // if any,
  // into memory

  // prints("go?");
  getc();
}
