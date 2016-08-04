// link list的節點struct宣告
typedef struct Node {
    int data;
    //self reference
    struct Node *nextPtr;

} node;

typedef node *nodePtr;


nodePtr GetNode();
int insertAfter(nodePtr, int, int);
void Traverse(nodePtr);
nodePtr preNode(nodePtr, int);
int deleteNode(nodePtr, int);
nodePtr createAll(int *, int);
