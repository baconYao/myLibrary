#include <stdio.h>
#include <stdlib.h>

void tempSwap(int*, int*);
void xorSwap(int*, int*);


int main(int argc, char *argv[])
{
    int a=1, b=2,c=3,d=4;
    // swap a,b
    tempSwap(&a,&b);
    printf("a:%d b:%d\n",a,b);
    // swap c,d
    xorSwap(&c,&d);
    printf("c:%d d:%d\n",c,d);

    return 0;
}

void tempSwap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b =temp;
}

void xorSwap(int *c, int *d)
{
    *c = *c ^ *d;
    *d = *c ^ *d;
    *c = *c ^ *d;
}

