/*
  User recursion function to implement bubble sort

*/

#include <stdio.h>


void bubble_srot(int *arr, int size);

int main(int argc, char **argv) {

  int array[20] = {55, 12, 76, 54, 34, 65, 77, 24, 18, 91, 72, -8, 51, 10, -22, -1, -5, 63, 19, 4};


  bubble_srot(array, 20);

  int i = 0;
  for(i = 0; i < 20; i++) {
    printf("%d\n", array[i]);
  }

  return 0;
}


void bubble_srot(int *arr, int size){
  if(size == 1) {
    return;
  }

  int i,tmp;
  for(i = 0; i < size-1; i++) {
    if(arr[i+1] < arr[i] ) {
      tmp = arr[i];
      arr[i] = arr[i+1];
      arr[i+1] = tmp;
    }
  }

  return bubble_srot(arr, size-1);

}

