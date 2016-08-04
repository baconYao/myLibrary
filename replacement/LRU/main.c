#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "library.h"



int main(int argc, char *argv[])
{
    int keepGo;
    if(argc < 2){
        printf("Sorry!\n");
        printf("You need input some parameter.\n");
        printf("Example:  ./a.out workload [-d]\n");
        keepGo = 0;
    } else  if(argc == 2){
        printf("Did not enter -d argument\n");
        printf("------------------------------\n");
        keepGo = 1;
    } else if (argc == 3){
        printf("You have selected a parameter [%s] .\n",argv[2]);
        printf("Your workload is %s .\n", argv[1]);
        printf("------------------------------\n");
        keepGo = 1;
    } else {
        printf("Sorry!\n");
        printf("You enter too much parameters\n");
        printf("Example:  ./a.out workload [-d]\n");
        keepGo = 0;
    }


    if(keepGo){
        // 紀錄最大的block number
        int maxBlockNumber = 0;
        // 紀錄block number 的數量
        int bloNuCount = 0;

        /* 初始化，第一次讀檔並記錄block number數量，以利新增array list */
        
        FILE *rPtr;
        int rBlockNum;
        if((rPtr = fopen(argv[1],"r")) == NULL){
            printf("First read error!\n");
            exit(1);
        }
        else {
            printf("Reading workload......\n");
            while(!feof(rPtr))
            {   
                // 讀資料
                fscanf(rPtr, "%d\n",&rBlockNum);
                if(rBlockNum >= maxBlockNumber){
                    maxBlockNumber = rBlockNum;
                }
                bloNuCount++;
            }
            fclose(rPtr);
        }
        printf("First read finish.\n\n\n");
        printf("------------------------------\n");


        /* 第二次讀檔，新增array list並開始執行LRU演算法 */
        // 新增一個array list
        DnodePtr Arr = initialArrayList(maxBlockNumber);
        // 第二次讀取workload，並且將資料輸進buffer內執行LRU演算法
        int srBlockNum;
        int preBlock = -1;   //紀錄上一個block number
        int needDelete = 0;  //是否執行踢除動作(若buffer cache已滿)
        int hitCount = 0;    //記錄hit count
        int firstBlkNm; // 記錄最前面的block number
        int lastBlkNm;  // 記錄最後面的block number
        int c;
        if((rPtr = fopen(argv[1],"r")) == NULL){
            printf("Second read error!\n");
            exit(1);
        }
        else {
            printf("Reading workload......\n");
            int i = 0;
            for(i = 0; i < bloNuCount; i++)
            {
                // 判斷buffer cache是否已滿
                if((i+1) * blockSize > bufferSize){
                    needDelete = 1;
                }
                // 讀資料
                fscanf(rPtr, "%d\n",&srBlockNum);
                LRU(Arr,i,srBlockNum,preBlock,needDelete,&hitCount,&firstBlkNm,&lastBlkNm);
                printf("%d\n",hitCount );
                // c = getchar();
                // DTraverse(Arr,firstBlkNm,maxBlockNumber);
                preBlock = srBlockNum;
            }
            fclose(rPtr);
        }
        printf("\n\nLRU finish.\n");
        printf("------------------------------\n");
        float hitRatio = (float)hitCount / (float)bloNuCount;
        printf("Hit ratio: %.3f\n",hitRatio );

    } else {
        exit(1);
    }
    


    return 0;
}
