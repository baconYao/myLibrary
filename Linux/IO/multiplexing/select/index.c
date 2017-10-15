#include <stdio.h>
#include <string.h>
#include <sys/select.h>

int main(int argc, char **argv) {

  int fd = 0;         //stdin
  char buf[11];
  int ret, sret;

  fd_set readfds;
  struct timeval timeout;


  while(1) {

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    sret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if(sret == 0) {               //timeout
      printf("sret = %d, timeout\n", sret);
    } else {
      printf("sret = %d\t", sret);
      memset((void *) buf, 0 , 11);
      ret = read(fd, (void *) buf, 10);
      printf("ret = %d\n", ret);
  
      if(ret != -1) {
        // buf[10] = '\0';
        printf(" buf = %s\n", buf);
      }
    }
  }

  return 0;
}