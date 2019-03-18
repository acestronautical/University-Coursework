#include <ext2fs/ext2_fs.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// define shorter TYPES, save typing efforts
typedef struct ext2_group_desc ext2_group_desc;
typedef struct ext2_ext2_super_block_block ext2_super_block;
typedef struct ext2_inode ext2_inode;
typedef struct ext2_dir_entry_2
    ext2_dir_entry_2; // need this for new version of e2fs

ext2_group_desc *gp;
ext2_super_block *sp;
ext2_inode *ip;
ext2_dir_entry_2 *dp;

#define BLKSIZE 1024
#define ISIZE 128

#define BITS_PER_BLOCK (8 * BLOCK_SIZE)
#define ext2_inodeS_PER_BLOCK (BLOCK_SIZE / sizeof(ext2_inode))

// Default dir and regulsr file modes
#define ext2_dir_entry_2_MODE 0040777
#define FILE_MODE 0100644
#define ext2_super_block_MAGIC 0xEF53
#define ext2_super_block_USER 0

// Proc status
#define FREE 0
#define BUSY 1
#define READY 2

// Table sizes
#define NMext2_inode 64
#define NMOUNT 4
#define NPROC 2
#define NFD 16
#define NOFT 32

// Open File Table
typedef struct Oft {
  int mode;
  int refCount;
  struct Minode *inodeptr;
  long offset;
} OFT;

// PROC structure
typedef struct Proc {
  int uid;
  int pid;
  int gid;
  int status;

  struct Minode *cwd;
  OFT *fd[NFD];

  struct Proc *next;
  struct Proc *parent;
  struct Proc *child;
  struct Proc *sibling;
} PROC;

// In-memory inodes structure
typedef struct Minode {
  ext2_inode ext2_inode; // disk inode
  int dev, ino;

  int refCount;
  int dirty;
  int mounted;
  struct Mount *mountptr;
} Mext2_inode;

// Mount Table structure
typedef struct Mount {
  int dev;
  int ninodes;
  int nblocks;
  int imap, bmap, iblk;
  struct Minode *mounted_inode;
  char name[256];
  char mount_name[64];
} MOUNT;
