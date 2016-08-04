#include <stdio.h>
#include <stdlib.h>

#include "library.h"


int main(int argc, char *argv[])
{
    // head
    nodePtr first = NULL;
    int data[6] = {7,5,33,6,9,0};

    // insert data to link list
    first = createAll(data, 6);
    // travel link list
    printf("Head -> ");
    Traverse(first);
    printf("\n");
    // delete
    printf("delete 6\n");
    nodePtr node = GetNode();
    node = preNode(first, 9);
    deleteNode(first, 6);
    Traverse(first);
    printf("\n");
    // insert after
    printf("insert 80 after 5\n");
    insertAfter(first, 5, 80);
    Traverse(first);
    printf("\n");

    return 0;
}

