//Author: Ace Cassidy

// PART 1: Partition Table
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
