/*
  Simple hash program by C laguage.
  https://www.youtube.com/watch?v=B7CdfZEMDXM
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

  return 0;
}