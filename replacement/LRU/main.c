#include "config.h"
#include "library.h"



int main(int argc, char *argv[])
{
    int keepGo;
    if(argc < 2){
        printf(RED_BOLD"Sorry!\n");
        printf("You need input some parameter.\n");
        printf("Example:  ./a.out workload [-d]\n");
        keepGo = 0;
    } else  if(argc == 2){
        printf(CYAN_BOLD_ITALIC"Did not enter -d argument\n");
        printf("------------------------------\n"RESET);
        keepGo = 1;
    } else if (argc == 3){
        printf(CYAN_BOLD_ITALIC"You have selected a parameter [%s] .\n",argv[2]);
        printf("Your workload is %s .\n", argv[1]);
        printf("------------------------------\n"RESET);
        keepGo = 1;
    } else {
        printf(RED_BOLD"Sorry!\n");
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
            printf(RED_BOLD"First read error!\n"RESET);
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
        int c = getchar();

        /* 第二次讀檔，新增array list並開始執行LRU演算法 */
        // 新增一個array list
        DnodePtr Arr = initialArrayList(maxBlockNumber);
        // 第二次讀取workload，並且將資料輸進buffer內執行LRU演算法
        int srBlockNum;
        int preBlock = -1;   //紀錄上一個block number
        int needDelete = 0;  //是否執行踢除動作(若buffer cache已滿)
        int hitCount = 0;    //記錄hit count
        int firstBlkNm= -1; // 記錄最前面的block number
        int lastBlkNm= -1;  // 記錄最後面的block number
        if((rPtr = fopen(argv[1],"r")) == NULL){
            printf(RED_BOLD"Second read error!\n"RESET);
            exit(1);
        }
        else {
            printf("Reading workload......\n");
            int i = 0;
            int key = 1;
            for(i = 0; i < bloNuCount; i++)
            {
                // 判斷buffer cache是否已滿
                if( (i > 0)  &&  key){
                    // int c = getchar();
                    // printf("!%d\n",DBlockNumberInCache(Arr,firstBlkNm,maxBlockNumber));
                    if( (DBlockNumberInCache(Arr,firstBlkNm,maxBlockNumber) == maxBlockCountInCache)) {
                        printf("Cache is fulled blocks\n");
                        // int c = getchar();
                        needDelete = 1;
                        key = 0;
                    }
                }
                // printf("%d\n",i );
                // 讀資料
                fscanf(rPtr, "%d\n",&srBlockNum);
                LRU(Arr,i,srBlockNum,preBlock,needDelete,&hitCount,&firstBlkNm,&lastBlkNm);
                // printf("%d\n",hitCount );
                // int c = getchar();
                // DTraverse(Arr,firstBlkNm,maxBlockNumber);

                preBlock = srBlockNum;
            }
            fclose(rPtr);
        }
        printf("\n\nLRU finish.\n");
        printf("------------------------------\n");
        float hitRatio = (float)hitCount / (float)bloNuCount;
        printf(YEL_BOLD"Hit ratio: %.3f\n",hitRatio );

    } else {
        exit(1);
    }
    


    return 0;
}
