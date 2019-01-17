//Author: Ace Cassidy

// PART 1: Partition Table
#include "lab1.h"

void myfdisk(char *file)
{
    char buf[512];
    int fd = open(file, O_RDONLY);
    read(fd, buf, 512);
    if (fd == -1)
        printf("Could not open file\n");
    struct partition *p = (struct partition *)&buf[0x1BE];

    printf("Device     Boot Start     End     Sectors    ID\n");
    for (int i = 0, pNum = 1; i < 4; i++, p++, pNum++)
    {
        printf("%s%d           %4d     %4d       %4d   %3x\n", file, pNum, p->start_sector, p->start_sector + p->nr_sectors - 1, p->nr_sectors, p->sys_type);

        if (p->sys_type == 5)
        {
            int extStart = p->start_sector;
            int offset = 0;
            struct partition *pExt = p;
            lseek(fd, extStart * 512, SEEK_SET);
            while (pExt->sys_type)
            {
                pNum++;
                read(fd, buf, 512);
                pExt = (struct partition *)&buf[0x1BE];
                int bootStart = pExt->start_sector + offset + extStart;
                printf("%s%d           %4d     %4d       %4d   %3x\n", file, pNum, bootStart, bootStart + pExt->nr_sectors - 1, pExt->nr_sectors, pExt->sys_type);
                pExt++;
                lseek(fd, (extStart + pExt->start_sector) * 512, SEEK_SET);
                offset = pExt->start_sector;
            }
        }
    }
}
