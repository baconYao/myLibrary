#include <stdio.h>
#include <string.h>
#include <sys/select.h>

int main(int argc, char **argv) {

  int fd = 0;         //stdin
  char buf[11];
  int ret;


  while(1) {
    memset((void *) buf, 0 , 11);
    ret = read(fd, (void *) buf, 10);
    printf("ret = %d\n", ret);

    if(ret != -1) {
      // buf[10] = '\0';
      printf(" buf = %s\n", buf);
    }
  }

  return 0;
}