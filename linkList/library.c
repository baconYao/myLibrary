#include <stdio.h>
#include <stdlib.h>

#include "library.h"

// link list的節點struct宣告
typedef Node {
    int data;
    //self reference
    struct Node *nextPtr;

} node;

typedef node *nodePtr;

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

// 在L串列中的m節點後插入新節點，d為資料內容
int insertAfter(nodePtr L, nodePtr m, int d)
{
    nodePtr n = GetNode();
    if(n == NULL){
        return 0;
    }

    n->data = d;
    n->nextPtr = NULL;

    if(m != NULL){
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
        printf("%d \t",startPtr->data);
        startPtr = startPtr->nextPtr;
    }
}

// 尋找L串列內m節點的前一個節點
nodePtr preNode(nodePtr L, nodePtr m)
{
    nodePtr startPtr = L;
    // 因為是單向list，所以透過迴圈來尋找節點
    while((startPtr != NULL) && (startPtr->nextPtr != m))
    {
        startPtr = startPtr->nextPtr;
    }

    // 若startPtr為NULL，代表沒找到
    return startPtr;
}


int deleteNode(nodePtr L, nodePtr m)
{
    nodePtr B;
    //要刪除的節點為第一個點
    if(L == m){
        // error
        return 2
    }

    B = preNode(L,m);
    if(B == NULL){
        return 0;
    }
    B->nextPtr = m->nextPtr;
    //釋放記憶體
    free(m);
    return 1;
}
