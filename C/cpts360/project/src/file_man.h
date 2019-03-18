#pragma once
#include <ext2fs/ext2_fs.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//// TYPEDEF ////

// define shorter TYPES for convenience
typedef struct ext2_group_desc group_desc;
typedef struct ext2_super_block super_block;
typedef struct ext2_inode inode;
typedef struct ext2_dir_entry_2 dir_entry;

//// CONST ////

// Block size
#define BLKSIZE 1024

// Block number of EXT2 FS on FD
#define SUPER_BLOCK 1
#define GROUP_DESC_BLOCK 2
#define ROOT_INODE 2

// Default dir and regular file modes
#define DIR_ENTRY_MOD 0x41ED
#define FILE_MODE 0x81AE
#define SUPER_BLOCK_MAGIC 0xEF53
#define SUPER_BLOCK_USER 0

// Proc status
#define PROC_FREE 0
#define PROC_BUSY 1

// file system table sizes
#define NMINODE 100
#define NMTABLE 10
#define NPROC 2
#define NFD 10
#define NOFT 40

//// STRUCT ////

// Open file Table AKA opened file instance
typedef struct oft {
  // file mode
  int mode;
  // number of PROCs sharing this instance
  int refCount;
  // pointer to minode of file
  struct minode *minodePtr;
  // byte offset for R|W
  int offset;
} OFT;

// PROC structure
typedef struct proc {
  struct proc *next;
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
  inode inode;
  // disk inode
  int dev, ino;
  // use count
  int refCount;
  // modified flag
  int dirty;
  // mounted flag
  int mounted;
  // mount table pointer
  struct mtable *mntPtr;
  // ignored for simple FS
  // int lock;
} MINODE;

// Mount Table structure
typedef struct mtable {
  // device number; 0 for PROC_FREE
  int dev;
  // from superblock
  int ninodes;
  int nblocks;
  // from superblock and group_desc
  int free_blocks;
  int free_inodes;
  // from group descriptor
  int bmap;
  int imap;
  // inodes start block
  int iblock;
  // mount point dir_entry pointer
  MINODE *mntDirPtr;
  // device name
  char devName[64];
  // mount point dir_entry name
  char mntName[64];
} MTABLE;

//// VAR ////

// in memory  inodes
MINODE minode[NMINODE];

// root mounted inode
MINODE *root;

// mount tables
MTABLE mtable[NMTABLE];

// Opened file instance
OFT oft[NOFT];

// PROC structures
PROC proc[NPROC];

// current executing PROC
PROC *running;

// number of inode and blocks
int ninode, nblocks;

// not sure
int bmap, imap, iblock;

// device
int dev;

// tokenized component string strings
char gline[25], *name[16];

// number of component strings
int nname;

//// FUNC ////

int run_file_manager(int argc, char const *argv[]);
int fs_init();
MINODE *mialloc();
int midalloc(MINODE *);
int get_block(int, int, char *);
int put_block(int, int, char *);
MINODE *iget(int, int);
int iput(MINODE *);
int tokenize(char *);
int search(MINODE *, char *);
int getino(char *);

int mount_root(char *);