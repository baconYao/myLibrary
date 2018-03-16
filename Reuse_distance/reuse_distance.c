/*
 *  利用LRU cache計算workload的reuse distance
 *  以double link list實作LRU cache, 再搭配hash table查詢增
 *  概念:
 *    當一個data到來時，先查詢hash table
 *      若有紀錄，代表此data已經在cache內
 *        則將此data移至MRU端，並且將reuse distance記錄至distanceCounter array
 *      若沒紀錄，代表此data不在cache內
 *        若cache沒有滿
 *          則將此data放在cache MRU端，且update hash table
 *        若cahce滿了
 *          則將cache LRU端的資料剔除，再將data放在cache MRU端，最後update hash table
 */

#include "reuse_distance.h"

/* 
 * [初始化cache]
 */
void initialize_cache() {
  int i;
  for(i = 0; i < NUM_OF_USER; i++) {
    cache[i].size = 0;
    cache[i].head = cache[i].tail = NULL;
  }
  printf("Initialize cache ok!\n");
}

void main(int argc, char **argv) {
  initialize_cache();
}