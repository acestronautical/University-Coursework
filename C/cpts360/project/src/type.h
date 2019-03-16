#include <ext2fs/ext2_fs.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// define shorter TYPES for convenience
typedef struct ext2_group_desc GD;
typedef struct ext2_super_block SUPER;
typedef struct ext2_inode INODE;
typedef struct ext2_dir_entry_2 DIR;

// Block size
#define BLKSIZE 1024

// Block number of EXT2 FS on FD
#define SUPERBLOCK 1
#define GDBLOCK 2
#define ROOT_INODE 2

// Default dir and regular file modes
#define DIR_MOD 0x41ED
#define FILE_MODE 0x81AE
#define SUPER_MAGIC 0xEF53
#define SUPER_USER 0

// Proc status
#define FREE 0
#define BUSY 1

// file system table sizes
#define NMINODE 100
#define NMTABLE 10
#define NPROC 2
#define NFD 10
#define NOFT 40

// Open File Table
typedef struct oft {
  int mode;
  int refCount;
  struct minode *minodePtr;
  int offset;
} OFT;

// PROC structure
typedef struct proc {
  struct Proc *next;
  int pid;
  int uid;
  int gid;
  int ppid;
  int status;
  struct minode *cwd;
  OFT *fd[NFD];
} PROC;

// In-memory inodes structure
typedef struct minode {
  INODE INODE;
  // disk inode
  int dev, ino;
  // use count
  int refCount;
  // modified flag
  int dirty;
  // mounted flag
  int mounted;
  // mount table pointer
  struct mount *mntPtr;
  // ignored for simple FS
  // int lock;
} MINODE;

// Open file Table AKA opened file instance
typedef struct oft {
  int mode;
  // number of PROCs sharing this instance
  int refCount;
  // pointer to minode of file
  MINODE *minodePtr;
  // byte offset for R|W
  int offset;
} OFT;

// Mount Table structure
typedef struct mtable {
  // device number; 0 for FREE
  int dev;
  // from superblock
  int ninodes;
  int nblocks;
  // from superblock and GD
  int free_blocks;
  int free_inodes;
  // from group descriptor
  int bmap;
  int imap;
  // inodes start block
  int iblock;
  // mount point DIR pointer
  MINODE *mntDirPtr;
  // device name
  char devName[64];
  // mount point DIR name
  char mntName[64];
} MTABLE;
