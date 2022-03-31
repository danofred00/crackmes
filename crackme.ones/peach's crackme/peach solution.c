/*
    #########################
    ###       KEYGEN      ###
    ###  Peach's Crackme  ###
    #########################
         By @Danofred0
    Create the 31/03.2022 at 08:10 PM 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define OP1 0X69420
#define OP2 0Xbb8
#define OP3 0X1f
#define OP4 0X1

int keygen(const char *uname, int length);

int main(void)
{
    char username[10];
    int length, key;

    printf("username : ");
    scanf("%s", username);

    length = strlen(username);
    
    if((length < 3) || (length >= 10)){
        printf("The length of the username most be greater than 3 and lesser than 11 \n");
        exit(EXIT_FAILURE);
    }
    
    key = keygen(username, length);
    printf("Key : %d\n", key);

    return 0;
}

int keygen(const char *uname, const int length)
{
    int key=1, eax, tmp;
    char current_char,
        *uname_cpy = (char *)malloc(length);

    if(uname_cpy == NULL)
        exit(-1);

    strcpy(uname_cpy, uname);
    printf("%s == %d\n", uname_cpy, strlen(uname_cpy));

    // boucle
    for(int i=0; i<length; i++)
    {
        uname_cpy += (int64_t)i;
        current_char = uname[i];
        key += current_char;
    }

    /*  mov eax,dword ptr ss:[rbp-0x24]
        imul eax,eax,0x69420 
        mov dword ptr ss:[rbp-0x24],eax */
    eax = key*OP1;

    //  sub dword ptr ss:[rbp-0x24],0xBB8
    key = eax - OP2;
    
    eax = key;
    tmp = eax >> OP3;
    eax += tmp;
    eax >>= OP4;

    key = eax - uname[0];
    return key;
}
