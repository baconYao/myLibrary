# LRU replacement
* Author:Pei-Yao Chang
* Date:2016/8/4
* Language: C

##Forder Contents
In this project, you can see `main.c`、`library.c`、`library.h`、`config.h`、`workload1.txt`.

### main.c
*	It's implement some logical code.


### library.c & library.h
*	These two files are used to implement LRU function.

### config.h
*	Be used to define some arguments.

### workload1.txt
*	Every value in this file means "block number"

## How to use
1.	Clone this project to your host
2. `gcc main.c library.c` , then it will product an executable file.
3. `./a.out workload1.txt [-d]`, then you can see the answer.  