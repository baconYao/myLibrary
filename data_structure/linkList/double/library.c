#include <stdio.h>
#include <stdlib.h>

#include "library.h"

DnodePtr DGetNode()
{
    DnodePtr newNode;
    //須強制轉型，也可寫成(node *)
    // malloc要求配置一個node所需的記憶體
    newNode = (DnodePtr) malloc(sizeof(Dnode));

    if(newNode == NULL){
        printf("Insufficient memory\n");
    }

    return newNode;
}


// 在L串列中的m節點後插入新節點，d為資料內容
int DinsertAfter(DnodePtr L, DnodePtr m, int d)
{
    DnodePtr n = DGetNode();
    if(n == NULL){
        return 0;
    }

    // 初始化
    n -> data = d;
    n -> lLinkPtr = NUll;
    n -> rLinkPtr = NUll;

    if(m != NULL){
        n -> lLinkPtr = m;
        n -> rLinkPtr = m -> rLinkPtr;
        if(m -> rLinkPtr != NULL){
            //若有下一節點，則該節點的左鏈結應該指向n
            m -> rLinkPtr -> lLinkPtr = n;
        }
        m -> rLinkPtr = n;
    } else {
        L = n;
    }
    return 1;
}


int DdeleteNode(DnodePtr L, DnodePtr m)
{
    // 若m是唯一節點
    if( (m -> lLinkPtr == NULL) && (m -> rLinkPtr == NULL)){
        L = NULL;
        free(m);
        return 1;
    }

    if((m -> lLinkPtr == NULL) || (m -> rLinkPtr == NULL)){
        return 0;
    }

    if( (m -> lLinkPtr != NULL) && (m -> rLinkPtr != NULL)){
        m -> lLinkPtr -> rLinkPtr = m -> rLinkPtr;
        m -> rLinkPtr -> lLinkPtr = m -> lLinkPtr;
    }

    free(m)
    return 1;
}


// 循序訪問並印出值,L為list的header
void DTraverse(nodePtr L)
{
    // 將startPtr指向第一個節點
    nodePtr startPtr = L;
    while(startPtr != NULL)
    {
        printf("%d -> ",startPtr->data);
        startPtr = startPtr->nextPtr;
    }
}

