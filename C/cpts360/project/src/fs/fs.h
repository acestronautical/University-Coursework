#ifndef _CPTS360_FS_H
#define _CPTS360_FS_H

#include "../debug/debug.h"
#include <ext2fs/ext2_fs.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//// TYPEDEF ////

// define shorter TYPES for convenience
typedef struct ext2_group_desc group_desc;
typedef struct ext2_super_block super_block;
typedef struct ext2_inode inode;
typedef struct ext2_dir_entry_2 dir_entry;

//// CONST ////

// Block size
#define BLKSIZE_1024 1024

// Inode numbers of EXT2 as defined in ext2fs.h
// EXT2_BAD_INO 1         Bad blocks inode
// EXT2_ROOT_INO 2        Root inode
// EXT4_USR_QUOTA_INO 3   User quota inode
// EXT4_GRP_QUOTA_INO 4   Group quota inode
// EXT2_BOOT_LOADER_INO 5 Boot loader inode
// EXT2_UNDEL_DIR_INO 6   Undelete directory inode
// EXT2_RESIZE_INO 7      Reserved group descriptors inode
// EXT2_JOURNAL_INO 8     Journal inode
// EXT2_EXCLUDE_INO 9     The "exclude" inode, for snapshots
// EXT4_REPLICA_INO 10    Used by non-upstream feature

// Proc status
#define PROC_FREE 0
#define PROC_BUSY 1

// file system table sizes
#define NUM_MINODES 100
#define NUM_MOUNT_ENTRIES 10
#define NUM_PROCS 2
#define NUM_FD 10
#define NUM_OFT 40

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
} oft;

// PROC structure
typedef struct proc {
  struct proc *next;
  int pid;
  int uid;
  int gid;
  int ppid;
  int status;
  struct minode *cwd;
  oft *fd[NUM_FD];
} proc;

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
  // mount entry pointer
  struct mount_entry *mount_entry;
  // ignored for simple FS
  // int lock;
} minode;

// Mount Entry structure
typedef struct mount_entry {
  // device file descriptor
  int dev_fd;
  // device root inode
  minode *dev_root;
  // device path ex: ~/project/exampledisk
  char dev_path[64];
  // mount path ex: / for root, /A or /B or /C ... for non-root
  char mnt_path[64];
  // superblock
  super_block dev_sb;
  // group_desc
  group_desc dev_gd;
} mount_entry;

// REMOVED
// bmap == dev_gd->bg_block_bitmap;
// imap == dev_gd->bg_inode_bitmap;
// iblock == dev_gd->bg_inode_table;

//// VAR ////

// in memory  inodes
minode minode_arr[NUM_MINODES];

// root mounted inode
minode *global_root;

// mount tables
mount_entry mount_entry_arr[NUM_MOUNT_ENTRIES];

mount_entry *root_mount;

// Opened file instance
oft oft_arr[NUM_OFT];

// PROC structures
proc proc_arr[NUM_PROCS];

// current executing PROC
proc *running;

// tokenized component string strings
char gline[25], *name[16];

int nname;

//// FUNC ////

int run_file_manager(int argc, char const *argv[]);
int fs_init();
minode *alloc_minode();
int free_minode(minode *);
int get_block(int, int, char *);
int put_block(int, int, char *);
minode *get_inode(int, int);
int put_inode(minode *);
int tokenize_path(char *);
int search_path(minode *, char *);
int search_inode(char *);
int mount_root(char *);
#endif