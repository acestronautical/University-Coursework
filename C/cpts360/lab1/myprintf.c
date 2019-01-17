//Author: Ace Cassidy

// PART 2: myprintf Function
#pragma once
#include "lab1.h"


char *ctable = "0123456789ABCDEF";

//helper prints unsigned u32 recursively
int rpu(u32 x, int Base)
{
    char c;
    if (x)
    {
        c = ctable[x % Base];
        rpu(x / Base, Base);
        putchar(c);
    }
}

//print unsigned in given base
int printu(u32 x, int Base)
{
    if (!x)
        putchar('0');
    else
        rpu(x, Base);
}

//prints an integer (x may be negative!!!)
int printd(int x)
{
    if (x < 0){
        x = -x;
        putchar('-');
    }
    printu(x, 10);
}

// prints x in HEX   (start with 0x )
int printx(u32 x)
{
    printu(x, 16);
}

//prints x in Octal (start with 0  )
int printo(u32 x)
{
    printu(x, 8);
}

//prints string
int prints(char *x)
{
    while(*x){
        putchar(*x);
        x++;
    }
}

//prints string by %s, unsigned integer by %u, char by %c,
//integer by %d, unsigned integer in OCT by %o, unsigned integer in HEX by %x
//ignores field width and precision
void myprintf(char *fmt, ...)
{
    u32 *args = (u32 *) &fmt + 1;
    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            switch (*fmt)
            {
            case 's':
                prints((char*)*args);
                break;
            case 'u':
                printu(*args, 10);
                break;
            case 'c':
                putchar(*args);
                break;
            case 'd':
                printd(*args);
                break;
            case 'o':
                printo(*args);
                break;
            case 'x':
                printx(*args);
                break;
            case '%':
                putchar('%');
                args--;
                break;
            default:
                putchar('%');
                putchar(*fmt);
                args--;
                break;
            }
            args++;
        }
        else
        {
            putchar(*fmt);
            if(*fmt == '\n')
                putchar('\r');
        }
        fmt++;
    }
}
