#include <stdio.h>
#include <stdlib.h>

#include "library.h"

#define RED_BOLD "\x1b[;31;1m"
#define BLU_BOLD "\x1b[;34;1m"
#define YEL_BOLD "\x1b[;33;1m"
#define RESET "\x1b[0;m"
#define GRN_BOLD "\x1b[;32;1m"

// 新建一個array list
DnodePtr initialArrayList(long maxBloNum)
{
    DnodePtr newArrList;
    //須強制轉型，也可寫成(node *)
    // malloc要求配置一個node所需的記憶體
    newArrList = (DnodePtr) malloc((maxBloNum+1) * sizeof(Dnode));

    if(newArrList == NULL){
        printf("Insufficient memory\n");
    }

    printf("Array List initialization is complete.\n");

    return newArrList;
}


/*  
    在L串列中加入新節點
    bn為block number也代表資料內容同時也是arr的索引值
    i為目前輸入到第幾筆資料(從0)開始
    pre為上一個block number 
    delete用來接收buffer cache是否已滿，若滿的話則會開始踢除block，1為滿了要開始踢除
*/
void LRU(DnodePtr Arr, long i, long bn, long pre, int delete, long *hitCount, long *firstBlkNm, long *lastBlkNm, int isFirstTimeMeetZero,int showDetail)
{
    // printf("\n\nExecuting LRU..%d\n",bn);
    // printf("Now BN: %ld ,firstBlkNm: %ld, lastBlkNm: %ld", bn, *firstBlkNm, *lastBlkNm);
    // int c = getchar();

    // 第一筆資料，初始化
    if(i == 0){
        Arr[bn].blockNum = bn;
        Arr[bn].lLinkPtr = NULL;
        Arr[bn].rLinkPtr = NULL;
        Arr[bn].dirty = 1;
        *firstBlkNm = bn;
        *lastBlkNm = bn;
        if(showDetail) {
            printf("\nFirst Block Number is : %ld\n",Arr[bn].blockNum);
        }
    } else {
        /* 此資料已存在 */
        if(Arr[bn].blockNum == bn && !isFirstTimeMeetZero){
            *hitCount += 1;
            if(showDetail) {
                printf(RED_BOLD"Block number: %ld\n",bn);
            }
        /* 搬移到Arr最前面 */
            // 搬移的是第一個block
            if(bn == *firstBlkNm){
                // do nothing
            } else if(bn == *lastBlkNm){    //搬移的是最後一個block
                // 將最後block的右鏈結指向第一個block
                Arr[bn].rLinkPtr = &Arr[*firstBlkNm];

                // 更新最後一個的block number的內容
                *lastBlkNm = Arr[bn].lLinkPtr->blockNum;
                Arr[*lastBlkNm].rLinkPtr = NULL;

                // 將victim block的左鏈結指向Head(NULL)
                Arr[bn].lLinkPtr = NULL;

                // 將"原"第一block的左鏈結指向"最新"的地一個block
                Arr[*firstBlkNm].lLinkPtr = &Arr[bn];
                *firstBlkNm = bn;
            } else {
                // 更新victim block的前block的右鏈結及後block的左鏈結
                Arr[bn].lLinkPtr->rLinkPtr = Arr[bn].rLinkPtr;
                Arr[bn].rLinkPtr->lLinkPtr = Arr[bn].lLinkPtr;

                // 將bn的左鏈結指向Head(NULL)
                Arr[bn].lLinkPtr = NULL;
                // 將bn的右鏈結指向first
                Arr[bn].rLinkPtr = &Arr[*firstBlkNm];
                // 將first的左鏈結指向bn
                Arr[*firstBlkNm].lLinkPtr = &Arr[bn];
                *firstBlkNm = bn;
            }
        } else {
        /*資料不存在*/
            if(showDetail) {
                printf(RESET"Block number: %ld\n",bn);
            }
            // buffer cache已滿，需踢除最後的block
            if(delete){
                if(showDetail) {
                    printf(GRN_BOLD"Delete\n");                    
                }
                Arr[*lastBlkNm].dirty = 0;
                Arr[*lastBlkNm].blockNum = -1;
                Arr[*lastBlkNm].rLinkPtr = NULL;
                *lastBlkNm = Arr[*lastBlkNm].lLinkPtr->blockNum;
                Arr[*lastBlkNm].rLinkPtr->lLinkPtr = NULL;
                Arr[*lastBlkNm].rLinkPtr = NULL;

            } 
            // 將新進的block加到最前頭，並將rLinkPtr指向"原"第一個block
            Arr[bn].blockNum = bn;
            Arr[bn].dirty = 1;
            Arr[bn].lLinkPtr = NULL;    //指向Head(NULL)
            Arr[bn].rLinkPtr = &Arr[pre];
            *firstBlkNm = bn;

            // 將前一個block的lLinkPtr指向最新進來的Block
            Arr[pre].lLinkPtr = &Arr[bn];
        }

    }
    printf(RESET);
}

// // 循序訪問並印出值
void DTraverse(DnodePtr Arr, long firstBlkNm, long maxBloNum)
{
    printf("****************Traverse\n");
    long i = 0;
    long value;
    long tmp = firstBlkNm;
    for(i = 0; i < maxBloNum;i++)
    {   
        value = Arr[tmp].blockNum;

        if(i == 0){
            printf("Head <-> %ld <-> ", value);
        } else if(Arr[tmp].rLinkPtr == NULL){
            printf("%ld \n",value);
        } else {
            printf("%ld <-> ",value);
        }
        if(Arr[tmp].rLinkPtr != NULL){
            tmp = Arr[tmp].rLinkPtr->blockNum;
        } else {
            break;
        }
    }    
    printf("\nTraverse****************\n");
}

// 計算cache內有多少block number，並回傳數量，用來判斷cache是否已滿
long DBlockNumberInCache(DnodePtr Arr, long firstBlkNm, long maxBloNum)
{
    long i = 0;
    long tmp = firstBlkNm;
    while(Arr[tmp].rLinkPtr != NULL){
        i++;
        tmp = Arr[tmp].rLinkPtr->blockNum;
    }

    return i;

}
