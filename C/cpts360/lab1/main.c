#include "lab1.h"

int main(int argc, char *argv[], char *env[])
{
    // PART 1: myfdisk Function
    printf("-----------this is a test of myfdisk-----------\n");
    myfdisk("vdisk");

    // PART 2: myprintf Function
    printf("\n-----------this is a test of myprintf-----------\n");
    myprintf("Test 1:\n%%d=%d %%d=%d %%c=%c %%s=%s %%x=%x %%o=%o\n", 456, -456, 'W', "Test", 10, 8);
    myprintf("Test 2:\ncha=%c string=%s dec=%d hex=%x oct=%o neg=%d\n", 'A', "this is a test", 100, 100, 100, -100);
    myprintf("Test 3:\nargc=%d ", argc);
    for (int i = 0; i < argc; i++)
        myprintf("argv[%d]=%s ", i, argv[i]);
    myprintf("\n\nenv=%s\n", *env);
    return 0;
}