#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int a[10];
  int *b = NULL;
  printf("%p\n", a);
  printf("%p\n", &a);
  printf("%p\n", &a[0]);
  printf("%d\n", sizeof(a));
  printf("%d\n", sizeof(a[1]+1));
  printf("%d\n", sizeof(a+1));
  printf("%d\n", sizeof(b));
  printf("%d\n", sizeof(b+1));

  return 0;
}