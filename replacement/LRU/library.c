#include <stdio.h>
#include <stdlib.h>

#include "library.h"

#define RED_BOLD "\x1b[;31;1m"
#define RESET "\x1b[0;m"


// 新建一個array list
DnodePtr initialArrayList(int maxBloNum)
{
    DnodePtr newArrList;
    //須強制轉型，也可寫成(node *)
    // malloc要求配置一個node所需的記憶體
    newArrList = (DnodePtr) malloc(maxBloNum * sizeof(Dnode));

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
void LRU(DnodePtr Arr, int i, int bn, int pre, int delete, int *hitCount, int *firstBlkNm, int *lastBlkNm)
{
    // printf("\nExecuting LRU..%d\n",bn);


    // 第一筆資料，初始化
    if(i == 0){
        Arr[bn].blockNum = bn;
        Arr[bn].lLinkPtr = NULL;
        Arr[bn].rLinkPtr = NULL;
        Arr[bn].dirty = 1;
        *firstBlkNm = bn;
        *lastBlkNm = bn;
    } else {
        /* 此資料已存在 */
        if(Arr[bn].dirty){
            *hitCount+=1;
        /* 搬移到Arr最前面 */
            // 搬移的是最後一個block
            if(bn == *lastBlkNm){
                printf(RED_BOLD"Block number: %d\n",bn);
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
            } else if(bn == *firstBlkNm){
                // do nothing
                printf(RED_BOLD"Block number: %d\n",bn);
            } else {
                printf(RED_BOLD"Block number: %d\n",bn);
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
            printf(RESET"Block number: %d\n",bn);
            // buffer cache已滿，需踢除最後的block
            if(delete){
                Arr[*lastBlkNm].dirty = 0;
                Arr[*lastBlkNm].blockNum = -1;
                Arr[*lastBlkNm].rLinkPtr = NULL;
                *lastBlkNm = Arr[*lastBlkNm].lLinkPtr->blockNum;
                Arr[*lastBlkNm].rLinkPtr->lLinkPtr = NULL;
                Arr[*lastBlkNm].rLinkPtr = NULL;

            } 
            // 將新進的block加到最前頭，並將rLinkPtr指向"原"第一個block
            Arr[bn].blockNum = bn;
            Arr[bn].lLinkPtr = NULL;    //指向Head(NULL)
            Arr[bn].rLinkPtr = &Arr[pre];
            Arr[bn].dirty = 1;
            *firstBlkNm = bn;

            // 將前一個block的lLinkPtr指向最新進來的Block
            Arr[pre].lLinkPtr = &Arr[bn];
        }

    }
    printf(RESET);
}

// // 循序訪問並印出值
void DTraverse(DnodePtr Arr, int firstBlkNm, int maxBloNum)
{
    printf("Traverse\n");
    int i = 0;
    int value;
    int tmp = firstBlkNm;
    for(i = 0; i < maxBloNum;i++)
    {   
        value = Arr[tmp].blockNum;

        if(i == 0){
            printf("Head <-> %d <-> ", value);
        } else if(Arr[tmp].rLinkPtr == NULL){
            printf("%d \n",value);
            printf("----------------------------\n\n");
        } else {
            printf("%d <-> ",value);
        }
        if(Arr[tmp].rLinkPtr != NULL){
            tmp = Arr[tmp].rLinkPtr->blockNum;
        } else {
            break;
        }
    }    
}

