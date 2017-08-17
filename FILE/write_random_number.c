#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{

    int a, i;
    srand(time(NULL));  
    /*
        進行寫入動作
    */
    FILE *wPtr;
    // 開啟一個名為file的txt檔
    if((wPtr = fopen("file.txt","w")) == NULL){
        printf("File could not be opend\n");
    }
    else {
        printf("Writing.......\n");
        for(i=0;i<1000000;i++){
            // 寫入資料
            fprintf(wPtr, "%d\n", a=(rand()%65536));
        }
        fclose(wPtr);
    }
    printf("Write finish.\n\n");
    
    return 0;
}
