/*
  Simple hash program by C laguage.
  利用double link list解決collision的問題
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_TABLE_SIZE 5       //指定hash table的大小

/* 定義hash data的struct */
typedef struct hash_node {
  unsigned long int value;    //data value
  struct hash_node *next;
  struct hash_node *prev;
} hash_node;

/* 定義hash table的struct */
typedef struct hash_table {
  int size;                //紀錄此key的list有幾筆data
  hash_node *head;         //指向第一個hash_node
  hash_node *tail;         //指向最後一個hash_node
} hash_table;

/* 
 * [查詢目標是否在hash table內]
 * @param {hash_table } table[] [要查詢的hash table]
 * @param {unsigned long int } insertValue [要查詢的目標]
 * return true/false    [目標在table內 / 目標不在table內] 
 */
bool search(hash_table table[], unsigned long int searchValue) {
  hash_node *tmp;
  tmp = table[searchValue%HASH_TABLE_SIZE].head;

  /* 檢查此key的list是否有資料存在 */
  if(table[searchValue%HASH_TABLE_SIZE].size == 0) {
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
 * @param {hash_table } table[] [要操作的hash table]
 * @param {unsigned long int } insertValue [要新增的目標]
 */
void insert(hash_table table[], unsigned long int insertValue) {
  hash_node *node = (hash_node *) malloc(sizeof(hash_node));
  node->value = insertValue;
  node->next = node->prev = NULL;
  
  /* 此list目前沒有資料 */
  if(table[insertValue%HASH_TABLE_SIZE].size == 0) {
    table[insertValue%HASH_TABLE_SIZE].head = table[insertValue%HASH_TABLE_SIZE].tail = node;
    table[insertValue%HASH_TABLE_SIZE].size++;
    return ;
  }
  
  node->prev = table[insertValue%HASH_TABLE_SIZE].tail;
  table[insertValue%HASH_TABLE_SIZE].tail->next = node;
  table[insertValue%HASH_TABLE_SIZE].tail = node;
  table[insertValue%HASH_TABLE_SIZE].size++;
}

/* 
 * [刪除已存在hash table內的資料, 須先使用search檢查是否已存在, 若不存在, 則不應該刪除]
 * @param {hash_table } table[] [要操作的hash table]
 * @param {unsigned long int } deleteValue [要刪除的目標]
 */
void delete(hash_table table[], unsigned long int deleteValue) {
  /* 此list目前有一筆資料 */
  if(table[deleteValue%HASH_TABLE_SIZE].size == 1) {
    free(table[deleteValue%HASH_TABLE_SIZE].head);      //釋放記憶體
    table[deleteValue%HASH_TABLE_SIZE].head = table[deleteValue%HASH_TABLE_SIZE].tail = NULL;
    table[deleteValue%HASH_TABLE_SIZE].size--;
    return ;
  }

  hash_node *tmp;     //用來指向要刪除的位址

   /* 若要刪除的資料是在head */
  if(table[deleteValue%HASH_TABLE_SIZE].head->value == deleteValue) {
    tmp = table[deleteValue%HASH_TABLE_SIZE].head;
    table[deleteValue%HASH_TABLE_SIZE].head = tmp->next;
    table[deleteValue%HASH_TABLE_SIZE].head->prev = NULL;
    free(tmp);
    table[deleteValue%HASH_TABLE_SIZE].size--;
    return;
  }

  /* 若要刪除的資料是在tail */
  if(table[deleteValue%HASH_TABLE_SIZE].tail->value == deleteValue) {
    tmp = table[deleteValue%HASH_TABLE_SIZE].tail;
    table[deleteValue%HASH_TABLE_SIZE].tail = tmp->prev;
    table[deleteValue%HASH_TABLE_SIZE].tail->next = NULL;
    free(tmp);
    table[deleteValue%HASH_TABLE_SIZE].size--;
    return;
  }

  /* 刪除屬於list中間的資料, 需慢慢查詢 */
  tmp = table[deleteValue%HASH_TABLE_SIZE].head->next;      //將起始位址設為head的下一個資料
  while(1) {
    if(tmp->value == deleteValue) {
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      free(tmp);
      table[deleteValue%HASH_TABLE_SIZE].size--;
      break;
    }
    if(tmp->next != table[deleteValue%HASH_TABLE_SIZE].tail) {
      tmp = tmp->next;
    } else {
      break;
    }
  }
}


/* 
 * [列出hash table的內容]
 * @param {hash_table } table[] [要查詢的hash table]
 */
void display(hash_table table[]) {
  int i;
  hash_node *tmp;
  printf("Key\tValue\n");  
  for(i = 0; i < HASH_TABLE_SIZE; i++) {
    printf("%d\t", i);      //print 「key」
    tmp = table[i].head;
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



int main(int argc, char ** argv) {
  int i;
  /* 建立hash table */
  hash_table hTable[HASH_TABLE_SIZE];
  /* 初始化hash table */
  for(i = 0; i < HASH_TABLE_SIZE; i++) {
    hTable[i].size = 0;
    hTable[i].head = hTable[i].tail =  NULL;
  }

  if(!search(hTable, 62)) {
    insert(hTable, 62);
  }
  if(!search(hTable, 222)) {
    insert(hTable, 222);
  }
  if(!search(hTable, 82)) {
    insert(hTable, 82);
  }
  if(!search(hTable, 11)) {
    insert(hTable, 11);
  }
  if(!search(hTable, 100)) {
    insert(hTable, 100);
  }
  if(!search(hTable, 44)) {
    insert(hTable, 44);
  }
  if(!search(hTable, 393)) {
    insert(hTable, 393);
  }
  if(!search(hTable, 82)) {
    printf("You should not see this in terminal!\n");
    insert(hTable, 82);
  }

  if(search(hTable, 393)) {
    delete(hTable, 393);
  }

  if(search(hTable, 82)) {
    delete(hTable, 82);
  }

  if(search(hTable, 393)) {
    printf("You should not see this in terminal!\n");
    delete(hTable, 393);
  }

  printf("\n");
  display(hTable);

  return 0;
}