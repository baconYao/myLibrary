#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_TABLE_SIZE 5       //指定hash table的大小
#define CACHE_SIZE 8         //unit: page
#define NUM_OF_USER 1           //user數量


static long int freeCacheSize[NUM_OF_USER] = {CACHE_SIZE};          //紀錄每個user的free cahce size, 初始化為cache 總大小
static long int hitCount[NUM_OF_USER] = {0};          //紀錄每個user的hit count
static long int missCount[NUM_OF_USER] = {0};          //紀錄每個user的miss count
static unsigned long int distanceCounter[NUM_OF_USER][CACHE_SIZE] = {0};      //紀錄reuse distance的counter

/* 定義page的struct */
typedef struct ghost_cache_page {
  unsigned long int diskBlkno;
  struct ghost_cache_page *prev;
  struct ghost_cache_page *next;
} ghost_cache_page;

/* 定義cache的struct */
typedef struct ghost_cache_list {
  unsigned long int size;       //cache 目前的大小，和freeCacheSize[NUM_OF_USER]總和 = CACHE_SIZE
  ghost_cache_page *head;
  ghost_cache_page *tail;
} ghost_cache_list;

/* 宣告user cache list */
ghost_cache_list ghostCache[NUM_OF_USER];

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

/* 建立hash table */
hash_table hTable[NUM_OF_USER][HASH_TABLE_SIZE];

/* 初始化cache */
void initialize_ghost_cache();
/* 處理到來的data */
void handle_coming_req(unsigned long int diskBlkno, int userNumber);
/* 查詢目標是否在hash table內 */
bool search_hash_table( unsigned long int searchValue, int userNumber);
/* 新增資料進hash table, 須先使用search檢查是否已存在, 若存在, 則不應該新增 */
void insert_hash_table(unsigned long int insertValue, int userNumber);
/* 刪除已存在hash table內的資料, 須先使用search檢查是否已存在, 若不存在, 則不應該刪除 */ 
void delete_hash_table(unsigned long int deleteValue, int userNumber);
/* 列出hash table的內容 */ 
void display_hash_table(int userNumber);
/* 紀錄reuse distance並且將data移動到MRU端 */ 
void record_and_move_data_to_mru(unsigned long int diskBlkno, int userNumber);
/* 新增data至ghost cache的MRU端 */ 
void add_new_data_to_ghost_cache(unsigned long int diskBlkno, int userNumber);
/* 列出ghost cache list的內容 */ 
void display_ghost_cache_list(int userNumber);
/* 打印訊息 */ 
void show_result();