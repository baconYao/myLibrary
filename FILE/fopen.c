#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     //for sleep() function

int main(void)
{
    unsigned int PC[3] = {1,2,50};
    unsigned int BlockNum[3] = {2,60,70};
    unsigned int Inode[3] = {3,12313,3232};

    int i;
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
        for(i=0;i<3;i++){
            // 寫入資料
            fprintf(wPtr, "%d %d %d\n",PC[i],Inode[i],BlockNum[i]);
        }
        fclose(wPtr);
    }
    printf("Write finish.\n\n");



    // sleep五秒
    sleep(5);

    /*
        進行讀取動作
    */
    FILE *rPtr;
    int rPC,rInode,rBlockNum;
    if((rPtr = fopen("file.txt","r")) == NULL){
        printf("File could not be read\n");
    }
    else {
        printf("Reading......\n\n");
        while(!feof(rPtr))
        {   
            // 讀資料
            fscanf(rPtr, "%d %d %d\n",&rPC,&rInode,&rBlockNum);
            printf("PC:%d Inode:%d BlockNum:%d\n",rPC,rInode,rBlockNum);
        }
        fclose(rPtr);
    }
    printf("\nRead finish.\n");
    
    return 0;
}
