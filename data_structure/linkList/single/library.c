#include <stdio.h>
#include <stdlib.h>

#include "library.h"



// 取得一個新節點
nodePtr GetNode()
{
    nodePtr NewNode;
    //須強制轉型，也可寫成(node *)
    // malloc要求配置一個node所需的記憶體
    NewNode = (nodePtr) malloc(sizeof(node));

    if(NewNode == NULL){
        printf("Insufficient memory!\n");
    }

    // 回傳新節點的位址，該位址存放在NewNode指標中
    return NewNode;
}

// 在L串列中的md節點後插入新節點，d為資料內容
int insertAfter(nodePtr L, int md, int d)
{
    nodePtr n = GetNode();
    if(n == NULL){
        return 0;
    }

    n->data = d;
    n->nextPtr = NULL;

    nodePtr m = L;
    while(m != NULL)
    {
        if(m -> data != md){
            m = m -> nextPtr;
        } else {
            break;
        }
    }

    if(m -> data == md){
        n->nextPtr = m->nextPtr;
        m->nextPtr = n;
    }
    else{       //串列原為空串列
        L = n;
    }
    return 1;
}

// 循序訪問並印出值,L為list的header
void Traverse(nodePtr L)
{
    // 將startPtr指向第一個節點
    nodePtr startPtr = L;
    while(startPtr != NULL)
    {
        printf("%d -> ",startPtr->data);
        startPtr = startPtr->nextPtr;
    }
}

// 尋找L串列內節點data為d的前一個節點
nodePtr preNode(nodePtr L, int d)
{
    nodePtr startPtr = L;
    // 因為是單向list，所以透過迴圈來尋找節點
    while((startPtr != NULL) && (startPtr->nextPtr->data != d))
    {
        // printf("%d\n", startPtr->data);
        startPtr = startPtr->nextPtr;
    }

    // 若startPtr為NULL，代表沒找到
    return startPtr;
}

// 刪除節點data為d的資料
int deleteNode(nodePtr L, int d)
{
    nodePtr B;
    //要刪除的節點為第一個點
    if(L -> nextPtr == NULL){
        L = NULL;
        free(L);
        return 1;
    }

    B = preNode(L,d);
    if(B == NULL){
        return 0;
    }
    // 要被刪除的點為m
    nodePtr m = B -> nextPtr;
    B -> nextPtr = m -> nextPtr;
    //釋放記憶體
    free(m);
    return 1;
}

nodePtr createAll(int *data, int size)
{
    // 初始一個link list
    nodePtr L = NULL;
    int i = 0;
    for(i = size-1; i >= 0; i--)
    {
        // 建立新的點
        nodePtr n = GetNode();
        if(n == NULL){
            exit(0);
        }
        n -> data = data[i];
        n -> nextPtr = L;
        L = n;
        printf("%d in\n", data[i]);
    }
    return L;
}


