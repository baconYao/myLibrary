#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 100

char global_String[MAXSTRLEN];

char * string_function_dynamic(char *astring) {
  char *s;
  s = malloc(MAXSTRLEN);    //creat a memory space at heap location, when we exist this function, the String s in the heap location still live at there.
  s[0] = 0;           //need this to initailize the buffer created by malloc
  strcat(s, "hello ");  
  strcat(s, astring);  
  strcat(s, "\n"); 
  return s; 
};

char * string_function(char astring[]) {
  strcat(global_String, "hello ");  
  strcat(global_String, astring);  
  strcat(global_String, "\n"); 
  return global_String; 
};


int main(int argc, char **argv) {
  printf("%s", string_function("Judy"));
  printf("%s", string_function_dynamic("Yao"));
  return 0;
};