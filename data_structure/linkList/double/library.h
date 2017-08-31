// 雙向link list的節點struct宣告
typedef struct DNode
{
    int data;
    // self-reference
    struct DNode *lLinkPtr;
    struct DNode *rLinkPtr;
} Dnode;

typedef Dnode *DnodePtr;


nodePtr DGetNode();
int DinsertAfter(nodePtr, nodePtr, int);
void DTraverse(nodePtr);
nodePtr DpreNode(nodePtr, nodePtr);
int DdeleteNode(nodePtr, nodePtr);
nodePtr DcreateAll(int *, int);
