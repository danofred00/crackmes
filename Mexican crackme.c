/*
    hi crackers, there is mexican crackme by @Danofred0
    try harder to bypass this !!!

    :) good luck 
*/

#include <stdio.h>
#include <unistd.h>

typedef enum {false, true} Bool;

void generate_flag(int len);
Bool print_flag = false;

void main(void)
{
    if(!print_flag)
        puts("try harder ...");
    else
        generate_flag(10);
}

void generate_flag(int len){
    char *flag = "flag{Danof4edx_flag}";
    printf("%s \n", flag);
}