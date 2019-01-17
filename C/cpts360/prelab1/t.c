
/************* t.c file ********************/
#include <stdio.h>
#include <stdlib.h>

int *FP;

int main(int argc, char *argv[], char *env[])
{
    int a, b, c;
    printf("-------------main-------------\n");

    printf("&argc=%x argv=%x env=%x\n", &argc, argv, env);
    printf("&a=%x &b=%x &c=%x\n", &a, &b, &c);

    //code to print values of argc and argv[] entries
    printf("argc=%d\n", argc);
    for(int i = 0; i < argc; i++)
        printf("argv[%d]=%s ", i, argv[i]);
    printf("\n");
    a = 1;
    b = 2;
    c = 3;
    A(a, b);
    printf("!exit main\n");
}

int A(int x, int y)
{
    int d, e, f;
    printf("-------------A-------------\n");
    //  C code to PRINT ADDRESS OF d, e, f
    printf("&d=%x &e=%x &f=%x\n", &d, &e, &f);
    d = 4;
    e = 5;
    f = 6;
    B(d, e);
    printf("!exit A\n");
}

int B(int x, int y)
{
    int g, h, i;
    printf("-------------B-------------\n");
    //  C code to PRINT ADDRESS OF g,h,i
    printf("&g=%x &h=%x &i=%x\n", &g, &h, &i);
    g = 7;
    h = 8;
    i = 9;
    C(g, h);
    printf("!exit B\n");
}

int C(int x, int y)
{
    int u, v, w, i, *p;
    printf("-------------C-------------\n");
    //  C code to PRINT ADDRESS OF u,v,w,i,p;
    printf("&u=%x &v=%x &w=%x &i=%x\n", &u, &v, &w, &i);
    u = 10;
    v = 11;
    w = 12;
    i = 13;

    //(2).  C code to print the stack frame link list.
    printf("-------------Stack Frames-------------\n");
    FP = (int *)getebp(); // FP = stack frame pointer of the C() function
    while(*FP){
        printf("%x =>", FP);
        FP = *FP;
    }
    printf("%x => null\n\n", FP);

    //(3). Print the stack contents from p to the frame of main()
    //     YOU MAY JUST PRINT 128 entries of the stack contents.
    printf("-------------Stack Contents-------------\n");
    p = (int *)&p;
    while(p != FP)
    {
        printf("Adress %x -> Hex %x\n", p, *p);
        p = p + 1;
    }
        printf("Adress %x -> Hex %x\n", p, *p);

    //(4). On a hard copy of the print out, identify the stack contents
    //     as LOCAL VARIABLES, PARAMETERS, stack frame pointer of each function.
}