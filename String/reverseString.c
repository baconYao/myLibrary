#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverse(char *input) {
  char *tmp;
  int i, length = strlen(input);
  tmp = (char *) malloc(length * sizeof(length));
  for(i = 0; i < length; i++) {
    tmp[i] = input[length - i - 1];
  }
  tmp[length] = '\0';
  return tmp;
}

int main(int argc, char **argv) {

  char input[100];
  printf("Please enter a String(max is 100 characters): ");
  scanf("%99s", input);
  printf("Th reverse string is:  %s\n", reverse(input));

  return 0;
}