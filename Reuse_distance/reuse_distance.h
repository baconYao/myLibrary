#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 5         //unit: page
#define NUM_OF_USER 1           //user數量


static long int freeCacheSize[NUM_OF_USER] = {CACHE_SIZE};          //紀錄每個user的free cahce size, 初始化為cache 總大小
static long int hitCount[NUM_OF_USER] = {0};          //紀錄每個user的hit count
static long int missCount[NUM_OF_USER] = {0};          //紀錄每個user的miss count
static unsigned long int distanceCounter[NUM_OF_USER][CACHE_SIZE] = {0};      //紀錄reuse distance的counter

typedef struct cache_page {
  unsigned long int diskBlkno;
  struct cache_page *prev;
  struct cache_page *next;
} cache_page;

typedef struct cache_list {
  unsigned long int size;       //cache 目前的大小，和freeCacheSize[NUM_OF_USER]總和 = CACHE_SIZE
  cache_page *head;
  cache_page *tail;
} cache_list;

/* 宣告user cache list */
cache_list cache[NUM_OF_USER];


/* 初始化cache */
void initialize_cache();