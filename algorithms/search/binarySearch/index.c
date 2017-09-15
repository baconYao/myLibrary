#include <stdio.h>

int binary_search(int *arr, int target, int first, int last);

int main(int argc, char const *argv[])
{
  int target, array[] = {1,2,3,4,5,6,7,8,9};
  printf("Enter an number you want to search: ");
  scanf("%d", &target);

  int result =  binary_search(array, target, 0, 8);

  if(result) {
    printf("the element is %d\n", result);
  } else {
    printf("Can't find the element.\n");
  }
  return 0;
}


int binary_search(int *arr, int target, int first, int last) {
  int i, middle;
  middle = ( first + last ) / 2;
  while(first <= last) {
    if(arr[middle] < target) {
      first = middle + 1;
    } else if(arr[middle] > target) {
      last = middle - 1;
    } else if (arr[middle] == target){
      printf("Find element at index: %d and ", middle);
      return arr[middle];                     //find the element
    }

    middle = ( first + last ) / 2;
  }

  return 0;
}
