#include <stdio.h>
#include <stdlib.h>
/* Logic: This is divide and conquer algorithm similar to Merge Sort. Unlike Merge Sort this does not require
          extra space. So it sorts in place. Here the partitioning step involves choosing a pivot and partitioning the array
          such that all elements less than or equal to pivot are to the left of it and all the elements
          which  are greater than or equal to the pivot are to the right of it. Recursively, sort the left
          and right parts.
*/

void QuickSort(int *array, int from, int to)
{
  if(from>=to)return;
  int pivot = array[from]; /*Pivot I am chosing is the starting element */
  /*Here i and j are such that in the array all elemnts a[from+1...i] are less than pivot,
    all elements a[i+1...j] are greater than pivot and the elements a[j+1...to] are which
    we have not seen which is like shown below.
    ________________________i_________________j___________
    |pivot|....<=pivot......|....>=pivot......|.........|
    If the new element we encounter than >=pivot the above variant is still satisfied.
    If it is less than pivot we swap a[j] with a[i+1].
   */
  int i = from, j, temp;
  for(j = from + 1;j <= to;j++)
  {
    if(array[j] < pivot)
    {
      i = i + 1;
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }
  /* Finally The picture is like shown below
    _______________________i____________________
    |pivot|....<=pivot......|....>=pivot......|
  */
  temp = array[i];
  array[i] = array[from];
  array[from] = temp;
  /* So we the array is now
    ____________________i______________________
    |...<=pivot......|pivot|....>=pivot......|
  */
  /*Recursively sort the two sub arrays */
  QuickSort(array,from,i-1);
  QuickSort(array,i+1,to);
}

int main()
{
  int number_of_elements;
  printf("Enter the number of the elements: ");
  scanf("%d",&number_of_elements);

  int array[number_of_elements];
  int iter;
  for(iter = 0;iter < number_of_elements;iter++)
  {
    printf("%d: ", iter);
    scanf("%d", &array[iter]);
  }
  /* Calling this functions sorts the array */
  QuickSort(array,0,number_of_elements-1);
  for(iter = 0;iter < number_of_elements;iter++)
  {
          printf("%d ",array[iter]);
  }
  printf("\n");
  return 0;
}
