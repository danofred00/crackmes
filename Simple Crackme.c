
/*
    Coded By @Danofred0
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

// ----------------------------
#define INDEX_TO_READ 5
#define PASS_LENGTH 11
#define UNAME_LENGTH 10

//--------------------------------
BOOL dbg = FALSE;
char key = 'X';

// -------------------------------
void gen(char *buffer, size_t buff_size);
int _strlen(char *string);
char *substring(char *string, int index);
void read_key(char* buffer, size_t size);

// -----------------------------
void crackme(void);
void print_header(void);
void exit_with_error(char *message);
int debugger_present(void);
//-------------------------------
int main(void)
{
    if (debugger_present())
    {
        exit_with_error("Debugger is finding !!!");
        exit(EXIT_FAILURE);
    }
    else {
        // optimisation legere du programme
        if (dbg) exit_with_error("Bad cracking !");

        srand(time(NULL));
        crackme();
    }

    return 0;
}
// --------------------------------
void crackme(void)
{
    char username[UNAME_LENGTH],
        password[2*PASS_LENGTH],
        good_password[PASS_LENGTH] = "",
        additional[INDEX_TO_READ] = "";

    print_header();

    printf("Enter your name : ");
    scanf_s("%s", username);

    if (_strlen(username) < 5 || _strlen(username) > 10)
        exit_with_error("min 4 caracters and max 10 caracters\n");

    printf("Enter your serial key here : ");
    scanf_s("%s", password);

    // generation de la cle
    gen(additional, sizeof(additional));

    strcat(good_password, substring(username, 5));
    
    for (int i = 5, j = 0; i < PASS_LENGTH; i++, j++)
        good_password[i] = additional[j];
    
    good_password[PASS_LENGTH - 1] = '\0';

    printf("Good password : %s \n", good_password);

    if (memcmp(password, good_password, sizeof(good_password)) != 0)
        exit_with_error("Incorrect serial key !\n");

}

void print_header(void)
{
    puts("*********************************");
    puts("**        SIMPLE CRACKME       **");
    puts("**        By @Danofred0        **");
    puts("**     https://crackmes.one    **");
    puts("*********************************\n");
}

void exit_with_error(char *message)
{
    printf("ERROR ! > %s \n", message);
    system("pause");
    exit(EXIT_FAILURE);
}

int debugger_present(void)
{
    if (IsDebuggerPresent())
    {
        dbg = TRUE;
        return 1;
    }
    return 0;
}
// --------------------------------
void gen(char *buffer, size_t buff_size)
{
    char all_chars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                        'h', 'i', 'j', 'k', 'l', 'm', 'o',
                        'p', 'q', 'r', 's', 't', 'u', 'v',
                        'w', 'x', 'y', 'z'}, current;

    for (unsigned int i = 0; i < buff_size; i++) {
        current = (all_chars[i] ^ key) % _strlen(all_chars);
        buffer[i] = all_chars[current];
    }
}

int _strlen(char *string)
{
    unsigned int len = 0, i=0;
    char current;
    
    while((current = string[i]) != '\0'){ len++; i++; }
    
    return len;
}

char *substring(char *string, int index)
{
    char *subkey = NULL; 

    if (index > _strlen(string))
        subkey = 0;

    else

        if ((subkey = (char*)malloc(sizeof(char) * index)) != NULL)
            memcpy(subkey, string, index);

    return subkey;
}
