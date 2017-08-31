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

void insert_max_heap(heap *h, int value) {
  h -> arr[++h -> size] = value;
  int child_index = h -> size;
  while(child_index > 1 && h -> arr[child_index] > h -> arr[child_index / 2]) {
    swap(&h -> arr[child_index], &h -> arr[child_index / 2]);
  }
}

void insert_min_heap(heap *h, int value) {
  h -> arr[++h -> size] = value;
  int child_index = h -> size;
  while(child_index > 1 && h -> arr[child_index] < h -> arr[child_index / 2]) {
    swap(&h -> arr[child_index], &h -> arr[child_index / 2]);
  }
}

int extract_max_heap(heap *h) {
  if(empty_heap(h)) {
    printf("Heap is empty!");
    return 0;
  }

  int value = h -> arr[1];
  h -> arr[1] = h -> arr[h -> size];
  h -> size--;
  int parentIndex = 1;
  int leftChildIndex, rightChildIndex;

  do {
    leftChildIndex = parentIndex * 2;
    rightChildIndex = parentIndex * 2 + 1;
    if(h -> arr[parentIndex] > max(h -> arr[leftChildIndex], h -> arr[rightChildIndex])) {
      break;
    }
    
    if(h -> size == leftChildIndex || h -> arr[leftChildIndex] > h -> arr[rightChildIndex]) {
      swap(&h -> arr[parentIndex], &h -> arr[leftChildIndex]);
      parentIndex = leftChildIndex;
    }
    else {
      swap(&h -> arr[parentIndex], &h -> arr[rightChildIndex]);
      parentIndex = rightChildIndex;
    }

  } while(parentIndex < h -> size);
  return value;
}

int extract_min_heap(heap *h) {
  if(empty_heap(h)) {
    printf("Heap is empty!");
    return 0;
  }

  int value = h -> arr[1];
  h -> arr[1] = h -> arr[h -> size];
  h -> size--;
  int parentIndex = 1;
  int leftChildIndex, rightChildIndex;

  do {
    leftChildIndex = parentIndex * 2;
    rightChildIndex = parentIndex * 2 + 1;
    if(h -> arr[parentIndex] < min(h -> arr[leftChildIndex], h -> arr[rightChildIndex])) {
      break;
    }
    
    if(h -> size == leftChildIndex || h -> arr[leftChildIndex] < h -> arr[rightChildIndex]) {
      swap(&h -> arr[parentIndex], &h -> arr[leftChildIndex]);
      parentIndex = leftChildIndex;
    }
    else {
      swap(&h -> arr[parentIndex], &h -> arr[rightChildIndex]);
      parentIndex = rightChildIndex;
    }

  } while(parentIndex < h -> size);
  return value;
}


int main(int argc, char **argv ) {
  heap *h = create_heap(100);
  insert_min_heap(h, 6);
  insert_min_heap(h, 3);
  insert_min_heap(h, 9);
  insert_min_heap(h, 5);
  insert_min_heap(h, 3);
  while(!empty_heap(h)) {
    printf("%d\n", extract_min_heap(h));
  }

  return 0;
}