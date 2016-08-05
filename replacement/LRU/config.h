#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_BOLD "\x1b[;31;1m"
#define BLU_BOLD "\x1b[;34;1m"
#define YEL_BOLD "\x1b[;33;1m"
#define GRN_BOLD "\x1b[;32;1m"
#define CYAN_BOLD_ITALIC "\x1b[;36;1;3m"
#define RESET "\x1b[0;m"


// 設置buffer cache的大小，預設為1G
int bufferSize = 1024 * 1024;

// 設置block size，預設為256KB
int blockSize = 256;
