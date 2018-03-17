/*
 *  利用LRU cache計算workload的reuse distance
 *  以double link list實作LRU cache, 再搭配hash table查詢
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
 * [查詢目標是否在hash table內]
 * @param {unsigned long int } insertValue [要查詢的目標]
 * return true/false    [目標在table內 / 目標不在table內]
 * @param {int } userNumber [user代號]
 */
bool search_hash_table(unsigned long int searchValue, int userNumber) {
  hash_node *tmp;
  tmp = hTable[userNumber-1][searchValue%HASH_TABLE_SIZE].head;

  /* 檢查此key的list是否有資料存在 */
  if(hTable[userNumber-1][searchValue%HASH_TABLE_SIZE].size == 0) {
    return false;
  }

  while(1) {
    if(tmp->value == searchValue) {
      return true;
    }
    if(tmp->next != NULL) {
      tmp = tmp->next;
    } else {
      break;
    }
  }
  return false;
}

/* 
 * [新增資料進hash table, 須先使用search檢查是否已存在, 若存在, 則不應該新增]
 * @param {unsigned long int } insertValue [要新增的目標]
 * @param {int } userNumber [user代號]
 */
void insert_hash_table(unsigned long int insertValue, int userNumber) {
  hash_node *node = (hash_node *) malloc(sizeof(hash_node));
  node->value = insertValue;
  node->next = node->prev = NULL;
  
  /* 此list目前沒有資料 */
  if(hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].size == 0) {
    hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].head = hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].tail = node;
    hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].size++;
    return ;
  }
  
  node->prev = hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].tail;
  hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].tail->next = node;
  hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].tail = node;
  hTable[userNumber-1][insertValue%HASH_TABLE_SIZE].size++;
}

/* 
 * [刪除已存在hash table內的資料, 須先使用search檢查是否已存在, 若不存在, 則不應該刪除]
 * @param {unsigned long int } deleteValue [要刪除的目標]
 * @param {int } userNumber [user代號]
 */
void delete_hash_table(unsigned long int deleteValue, int userNumber) {
  /* 此list目前有一筆資料 */
  if(hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].size == 1) {
    free(hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].head);      //釋放記憶體
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].head = hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].tail = NULL;
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].size--;
    return ;
  }

  hash_node *tmp;     //用來指向要刪除的位址

   /* 若要刪除的資料是在head */
  if(hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].head->value == deleteValue) {
    tmp = hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].head;
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].head = tmp->next;
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].head->prev = NULL;
    free(tmp);
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].size--;
    return;
  }

  /* 若要刪除的資料是在tail */
  if(hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].tail->value == deleteValue) {
    tmp = hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].tail;
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].tail = tmp->prev;
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].tail->next = NULL;
    free(tmp);
    hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].size--;
    return;
  }

  /* 刪除屬於list中間的資料, 需慢慢查詢 */
  tmp = hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].head->next;      //將起始位址設為head的下一個資料
  while(1) {
    if(tmp->value == deleteValue) {
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      free(tmp);
      hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].size--;
      break;
    }
    if(tmp->next != hTable[userNumber-1][deleteValue%HASH_TABLE_SIZE].tail) {
      tmp = tmp->next;
    } else {
      break;
    }
  }
}

/* 
 * [列出hash table的內容]
 * @param {int } userNumber [user代號]
 */
void display_hash_table(int userNumber) {
  int key;
  hash_node *tmp;
  printf("Key\tValue\n");  
  for(key = 0; key < HASH_TABLE_SIZE; key++) {
    printf("%d\t", key);      //print 「key」
    tmp = hTable[userNumber-1][key].head;
    /* 若此key的list沒有資料，則換下一個key的list */
    if(tmp == NULL) {
      printf("NULL\n");
      continue;
    }
    while(1) {
      printf("%lu -> ", tmp->value);
      if(tmp->next != NULL) {
        tmp = tmp->next;
      } else {
        break;
      }
    } 
    printf("NULL\n");
  }
}

/* 
 * [初始化cache]
 */
void initialize_cache() {
  int i;
  for(i = 0; i < NUM_OF_USER; i++) {
    cache[i].size = 0;
    cache[i].head = cache[i].tail = NULL;
  }
}

/* 
 * [紀錄reuse distance並且將data移動到MRU端]
 * @param {unsigned long int } diskBlkno [要移動到MRU端的data]
 * @param {int } userNumber [user代號]
 */
void record_and_move_data_to_mru(unsigned long int diskBlkno, int userNumber) {
  /* data在head, 只記錄reuse distance，不移動data */
  if(cache[userNumber-1].head->diskBlkno == diskBlkno) {
    distanceCounter[userNumber-1][0]++;       //distance 0 counter ++
    return;
  }
  
  /* data在tail */
  if(cache[userNumber-1].tail->diskBlkno == diskBlkno) {
    distanceCounter[userNumber-1][cache[userNumber-1].size-1]++;    //紀錄distance counter
    /* 移動data至MRU端 */
    cache_page *tmp;
    tmp = cache[userNumber-1].tail;
    cache[userNumber-1].tail = cache[userNumber-1].tail->prev;
    cache[userNumber-1].tail->next = NULL;
    tmp->next = cache[userNumber-1].head;
    tmp->prev = NULL;
    cache[userNumber-1].head->prev = tmp;
    cache[userNumber-1].head = tmp;
    return;
  }

  /* data在中間 */
  int i = 0;
  cache_page *tmp;
  tmp = cache[userNumber-1].head;
  while(tmp != NULL) {
    if(tmp->diskBlkno == diskBlkno) {
      distanceCounter[userNumber-1][i]++;         //紀錄distance counter
      /* 移動data至MRU端 */
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      tmp->prev = NULL;
      tmp->next = cache[userNumber-1].head;
      cache[userNumber-1].head->prev = tmp;
      cache[userNumber-1].head = tmp;
      return;
    }
    tmp = tmp->next;
    i++;
  }

}

/* 
 * [新增data到cache MRU端，並且update hash table]
 * @param {unsigned long int } diskBlkno [要移動到MRU端的data]
 * @param {int } userNumber [user代號]
 */
void add_new_data_to_cache(unsigned long int diskBlkno, int userNumber) {
  /* 檢查cache 有沒有滿 */
  if(cache[userNumber-1].size == CACHE_SIZE) {        //若cache 滿了
    /* 先將hash table update(剔除cache tail的diskBlkno data)*/
    delete_hash_table(cache[userNumber-1].tail->diskBlkno, userNumber);
    /* 將hash table update(將diskBlkno data新增至hash table) */
    insert_hash_table(diskBlkno, userNumber);
    /* 再剔除LRU端的data  */
    cache_page *tmp;
    tmp = cache[userNumber-1].tail;
    cache[userNumber-1].tail = cache[userNumber-1].tail->prev;
    cache[userNumber-1].tail->next = NULL;
    free(tmp);
    /* 再將new data新增進cache head(MRU端)*/
    cache_page *new = (cache_page*)malloc(sizeof(cache_page));
    new->diskBlkno = diskBlkno;
    new->prev = NULL;
    new->next = cache[userNumber-1].head;
    cache[userNumber-1].head->prev = new;
    cache[userNumber-1].head = new;
  } else {      //若cache沒有滿
    /* 先將hash table update(將diskBlkno data新增至hash table) */
    insert_hash_table(diskBlkno, userNumber);
    /* 若沒有任何data在cache內 */
    if(cache[userNumber-1].size == 0) {
      cache_page *new = (cache_page*)malloc(sizeof(cache_page));
      new->diskBlkno = diskBlkno;
      new->prev = new->next = NULL;
      cache[userNumber-1].head = cache[userNumber-1].tail = new;
    } else {
      /* 將new data新增進cache head(MRU端)*/
      cache_page *new = (cache_page*)malloc(sizeof(cache_page));
      new->diskBlkno = diskBlkno;
      new->prev = NULL;
      new->next = cache[userNumber-1].head;
      cache[userNumber-1].head->prev = new;
      cache[userNumber-1].head = new;
    }
    cache[userNumber-1].size++;
    
  }
}

/* 
 * [處理到來的data]
 * @param {unsigned long int } diskBlkno [data]
 * @param {int } userNumber [user代號]
 */
void handle_coming_req(unsigned long int diskBlkno, int userNumber) {
  /* 將data丟進hash table查詢 */
  if(search_hash_table(diskBlkno, userNumber)) {      //資料存在table，表示也存在cache
    hitCount[userNumber-1]++;
    record_and_move_data_to_mru(diskBlkno, userNumber);     //紀錄reuse distance並且將data移動到MRU端
  } else {        //資料存不在table，表示也不存在cache
    missCount[userNumber-1]++;
    add_new_data_to_cache(diskBlkno, userNumber);
  }
}

/* 
 * [列出cache list的內容]
 * @param {int } userNumber [user代號]
 */
void display_cache_list(int userNumber) {
  int key;
  cache_page *tmp;
  tmp = cache[userNumber-1].head;
  printf("\nUser%d Cache element number:%d\n", userNumber, cache[userNumber-1].size);  
  while(tmp != NULL) {
    printf("%lu -> ", tmp->diskBlkno);
    tmp = tmp->next;
  }
  printf("NULL\n");
}

/* 
 * [打印訊息]
 */
void show_result() {
  int i, j;
  for(i = 0; i < NUM_OF_USER; i++) {
    printf("Hit count: %d\tMiss count:%d\tHit Ratio:%f\n", hitCount[i], missCount[i], (double)hitCount[i]/(double)(hitCount[i]+missCount[i]));
    for(j = 0; j < CACHE_SIZE; j++) {
      printf("D%d: %d\n", j, distanceCounter[i][j]);
    }
  }
}

int main(int argc, char **argv) {
  initialize_cache();
  int i;
  
  handle_coming_req(1, 1);
  handle_coming_req(2, 1);
  handle_coming_req(3, 1);
  handle_coming_req(40, 1);
  handle_coming_req(4, 1);
  handle_coming_req(1, 1);
  handle_coming_req(9, 1);
  handle_coming_req(29, 1);
  handle_coming_req(29, 1);
  handle_coming_req(19, 1);
  handle_coming_req(4, 1);
  handle_coming_req(29, 1);
  handle_coming_req(2, 1);
  handle_coming_req(35, 1);
  handle_coming_req(40, 1);
  
  display_hash_table(1);
  display_cache_list(1);
  show_result();
  return 0;
}