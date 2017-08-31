/*
  Simple hash program by C laguage.
  https://www.youtube.com/watch?v=B7CdfZEMDXM
  furture work:
    1. 增加insert function
    2. 解決collision問題
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct hash_table {
  int key;
  int value;
} hash_table;

void display(hash_table table[], int size) {
  int i;
  printf("Key\tValue\n");  
  for(i = 0; i < size; i++) {
    printf("%d\t%d\n", table[i].key, table[i].value);
  }
}

void serach(hash_table table[], int size) {
  int i;
  printf("Enter the element you want to search: ");
  scanf("%d", &i);
  if(table[ i % size ].value == i) {
    printf("The element exist at %d\n", i % size);
  } else {
    printf("The element does not exist.\n");
  }
}

int main(int argc, char ** argv) {
  int size, i, tmp;
  printf("Enter the size of the hash table:");
  scanf("%d", &size);

  // 建立hash table
  hash_table hTable[size];
  printf("Enter the elements:");
  for(i = 0; i < size; i++) {
    scanf("%d", &tmp);
    hTable[tmp % size].value = tmp;
    hTable[tmp % size].key = tmp % size;
  }

  printf("\n");
  display(hTable, size);
  serach(hTable, size);

  return 0;
}