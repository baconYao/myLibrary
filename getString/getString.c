/*
    Refference:
        http://archerworks.blogspot.tw/2010/07/cstatic.html
        http://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
*/


#include <stdio.h>
#include <stdlib.h>

#define SIZE 100


char *GetString(void);

int main(int argc, char *argv[])
{
    char *inputString;

    inputString = GetString();

    printf("%s\n",inputString);
    printf("%p\n",inputString);

    return 0;
}


char *GetString(void)
{   
    static char input[SIZE];

    printf("Use gets function to get string!\n");
    printf("Please input data:");
    gets(input);
    printf("Your input is \'%s\' \n",input);

    return input;
}
