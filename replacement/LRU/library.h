// 雙向link list的節點struct宣告
typedef struct DNode
{
    int blockNum;
    // 是否有資料,0 is false, 1 is ture
    int dirty;
    // self-reference
    struct DNode *lLinkPtr;
    struct DNode *rLinkPtr;
} Dnode;

typedef Dnode *DnodePtr;


DnodePtr initialArrayList(int);
void LRU(DnodePtr, int, int, int, int, int *, int *, int *);
void DTraverse(DnodePtr, int, int);
int DBlockNumberInCache(DnodePtr, int, int);
// DnodePtr DpreNode(DnodePtr, DnodePtr);
// int DdeleteNode(DnodePtr, DnodePtr);
// DnodePtr DcreateAll(int *, int);
