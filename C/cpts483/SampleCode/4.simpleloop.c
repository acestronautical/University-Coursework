/*
 * 4.simpleloop.c
 * Copyright (C) 2020 Aravind SUKUMARAN RAJAM (asr) <aravind_sr@outlook.com>
 *
 * Distributed under terms of the GNU LGPL3 license.
 */

#include <stdio.h>


int main(int argc, char *argv[])
{
    int s = 0;

    for (int i = 0; i < argc; ++i)
    {
        s += i + argc * argc * argc;

    }

    printf("%d\n", s );
    return 0;
}


