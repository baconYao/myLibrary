#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct heap {
  int size;
  int *arr;
} heap; 

heap *create_heap(int max_size) {
  heap *h = (heap *) malloc(sizeof(heap));
  h -> arr = (int *) malloc(sizeof(int) * max_size);
  h -> size = 0;
  int i;
  for(i = 0; i < max_size; i++) {
    h -> arr[i] = 0;
  }
  return h;
}

bool empty_heap(heap *h) {
  return h -> size ==0;
}

void swap(int *nb1, int *nb2) {
  int tmp = *nb1;
  *nb1 = *nb2;
  *nb2 = tmp;
}

int max(int nb1, int nb2) {
  return nb1 > nb2 ? nb1 : nb2;
}

int min(int nb1, int nb2) {
  return nb1 < nb2 ? nb1 : nb2;
}

int main(int argc, char **argv ) {

  return 0;
}