// 雙向link list的節點struct宣告
typedef struct DNode
{
    long blockNum;
    // 是否有資料,0 is false, 1 is ture
    int dirty;
    // self-reference
    struct DNode *lLinkPtr;
    struct DNode *rLinkPtr;
} Dnode;

typedef Dnode *DnodePtr;


DnodePtr initialArrayList(long);
void LRU(DnodePtr, long, long, long, int, long *, long *, long *, int, int);
void DTraverse(DnodePtr, long, long);
long DBlockNumberInCache(DnodePtr, long, long);

