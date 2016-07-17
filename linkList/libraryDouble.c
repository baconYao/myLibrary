#include <stdio.h>
#include <stdlib.h>

#include "libraryDouble.h"


// 雙向link list的節點struct宣告
typedef struct DNode
{
    int data;
    // self-reference
    struct DNode *lLinkPtr;
    struct DNode *rLinkPtr;
} Dnode;

typedef Dnode *DnodePtr;
