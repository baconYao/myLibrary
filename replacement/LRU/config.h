#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_BOLD "\x1b[;31;1m"
#define BLU_BOLD "\x1b[;34;1m"
#define YEL_BOLD "\x1b[;33;1m"
#define GRN_BOLD "\x1b[;32;1m"
#define CYAN_BOLD_ITALIC "\x1b[;36;1;3m"
#define RESET "\x1b[0;m"

/*
  設置buffer cache(memory)的大小，預設為512MB
    一個page = 4KB
    一個block = 64個page = 256KB
    1MB = 4個block = 256 * 4
    1GB = 1000MB = 1000 * 4個block = 1000 * 256 * 4
*/

// 設置block size，預設為4KB
long blockSize = 4;

// set memory size = 512 MB
long bufferSize = 512 * 256 * 4;


#define maxBlockCountInCache bufferSize/blockSize
