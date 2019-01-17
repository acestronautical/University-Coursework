//Author: Ace Cassidy

// PART 1: Partition Table

// Write a C progrom to display the partition table of the vdisk in
// (1). Linux fdisk 'p' output form for the first 4 partitions (%40),
// (2). including ALL the extend partitions (%60) <== YOU BETTER DO THIS !!!!.
// Turn in a printed HARD COPY containing your work.
// 1. OBJECTIVES
//    Partition table, fdisk, structures in C, open-read files

// 2 Partition Table:

// A disk (floppy disk, hard disk, USB drive, SD cards, etc.) consists of 512-byte
// sectors, which are counted linearly as sector 0,1,2,....

// A disk is usually divided into several partitions. The partitions are recorded
// in a partition table at the beginning (the 0th sector) of the disk, called the
// Master Boot Record (MBR). Inside the MBR, the partition table begins at the
// byte offset 0x1BE. The Partitin Table contains 4 entries, each 16 bytes long,
// defined in the following C structure.

// typedef unsigned char  u8;
// typedef unsigned short u16;
// typedef unsigned int   u32;

// struct partition {
// 	u8 drive;             /* drive number FD=0, HD=0x80, etc. */

// 	u8  head;             /* starting head */
// 	u8  sector;           /* starting sector */
// 	u8  cylinder;         /* starting cylinder */

// 	u8  sys_type;         /* partition type: NTFS, LINUX, etc. */

// 	u8  end_head;         /* end head */
// 	u8  end_sector;       /* end sector */
// 	u8  end_cylinder;     /* end cylinder */

// 	u32 start_sector;     /* starting sector counting from 0 */
// 	u32 nr_sectors;       /* number of of sectors in partition */
// };

// heads, sectors, cylinders are for old floppy disks.
// Hard disks only use start_sector and nr_sectors.

// Each partition has a type, which indicates what kind of file system the
// partition MAY contain. Consult Linux's fdisk to see the partition types.

// If a partition is EXTEND type (type=5), the partition's area may be further
// divided into more partitions. The extended partitions forms a LINK-LIST as the
// following diagram shows.
// ------------------------------------------------------------------------------
// Assume P4 is EXT type:

// P4's beginSector = localMBR
//                      P5's beginSector# relative to beginSector
//                      P6's MBR's sector# = localMBR
//                          (r.e. to P4)       P6's beginSector#
//                                             P7's MBR r.e. to P4 --> etc.

// The first sector of each extended partition is a localMBR. Each localMBR has a
// partition table which contains only 2 entries. The first entry defines the start
// sector and size of the extended partition. The second entry points to the next
// localMBR. All the localMBR's sector numbers are relative to P4's start sector.
// As usual, the link list ends with a 0.
// -------------------------------------------------------------------------------

// Since use fdisk on hard disks is risky, we shall use a VIRTUAL disk for this
// assignment. A virtual disk is just a file but its contents are exactly the same
// as a REAL disk. Download the file ~cs360/samples/LAB1/vdisk to YOUR Linux.
// Then, run       fdisk vdisk
//                  'p' : to see the partition table
//                  'q' : to quit fdisk

//                       REQUIREMENTS

// Write a C progrom to display the partition table of the vdisk in

// (1). Linux fdisk 'p' output form for the first 4 partitions (%40),
// (2). including ALL the extend partitions (%60) <== YOU BETTER DO THIS !!!!.

// Turn in a printed HARD COPY containing your work.
#include "lab1.h"

void myfdisk(char *file)
{

    int offset = 446;
    struct partition *p = 0;
    int i = 0;
    printf("Device     Boot Start     End     Sectors    ID\n");
    int fd = open(file, O_RDONLY);

    u8 *buff = malloc(4 * sizeof(struct partition));
    if (fd == -1)
        return;
    lseek(fd, offset, SEEK_SET);
    read(fd, buff, 4 * sizeof(struct partition));
    p = (struct partition *)buff;
    for (i = 0; i < 4; i++, p++)
        printf("%s%d           %4d     %4d       %4d   %3x\n", file, i + 1, p->start_sector, p->start_sector + p->nr_sectors - 1, p->nr_sectors, p->sys_type);
    p--;
    int p4Start = p->start_sector;
    while (p->sys_type)
    {
        int numSectors = p4Start + p->start_sector; 
        lseek(fd, numSectors * 512 + offset, SEEK_SET);
        read(fd, buff, 2 * sizeof(struct partition));
        p = (struct partition *)buff;
        printf("%s%d           %4d     %4d       %4d   %3x\n", file, i + 1, p->start_sector + numSectors, p->start_sector + p->nr_sectors + numSectors - 1, p->nr_sectors, p->sys_type);
        p++, i++;
    }
}
