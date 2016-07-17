#include <stdio.h>
 
typedef struct list {
    char *name;
    //self reference
    struct list *nextPtr;
} List;
 
int main(void)
{
    List a, b, c, *startPtr;
     
    a.name = "John";
    b.name = "Mary";
    c.name = "Tony";
     
    startPtr = &a;
    a.nextPtr = &b;
    b.nextPtr = &c;
    // c is the last point, so c's nexPtr need to be pointed to "NULL"
    c.nextPtr = NULL;
     
    while (startPtr != NULL) {
        printf("%s\n", startPtr->name);
        startPtr = startPtr->nextPtr;
    }
 
    return 0;
}
