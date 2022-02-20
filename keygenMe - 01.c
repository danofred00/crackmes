/*
    hi guys, there is a simple Keygen Me
    Just try harder to generate a good serial
    code.
    
    :) Good luck
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_USER_NAME 100
#define MAX_KEY_LENGTH MAX_USER_NAME
#define BUFFER_SIZE 128
#define COUNT 10

char *getEncrytKey(const char *uName);
int _strlen(const char *string); // calcul automatiquement la longueur d'une chaine
void clearBuffer(char *buffer); //  here we cleaning the buffer
void ExitWithError(const char *message);
void tryToKeygenMe(int count); // this function are called if the user select opt 2
void printTitle(void); // main title
int _strcmpKey(const char *string1, const char *string2); // return 1 if the two strings are equals and 0 else
void printRules(void); // rules of this challenge


int main(void)
{
    printTitle();
    
    int choice;
    printf("(1) - rules \n");
    printf("(2) - start Training \n");
    printf(" Select an option : ");
    scanf("%d", &choice);

    // start switching ...
    switch (choice)
    {
    case 1:
        printRules();
        break;
    case 2:
        tryToKeygenMe(COUNT);
        break;
    default:
        printf("Please do a correct choice ! \n");
        break;
    }
    
    system("pause");
    return 0;
}

void tryToKeygenMe(int count){

    char uName[MAX_USER_NAME],
         serialKey[MAX_KEY_LENGTH],
         buffer[BUFFER_SIZE];

    // the username must be 4 caracters minimum
    do{
        printf(" Enter Your Username (4 chars at min) : "); // ask the user name
        scanf("%s", uName);
        clearBuffer(buffer);
    }while(_strlen(uName) < 4);

    do{
        count--;

        printf(" Password : ");
        scanf("%s", serialKey);
        clearBuffer(buffer);

        if(_strcmpKey(serialKey, getEncrytKey(uName)))
            printf("Good Password ! \n");
        else
        {
            printf("-> (%d / %d)\n", (COUNT-count), COUNT);
            printf("Wrong password for the username \"%s\": ! Try again ... \n", uName);
        }

        if(count == 0)
            printf("Just try at the next time. GoodBye :) \n");
    } while (count>0);

    printf("\n");
    
}

void printTitle(void){
    puts("\t*****************************");
    puts("\t*                           *");
    puts("\t*          KEYGEN ME        *");
    puts("\t*        By @Danofred       *");
    puts("\t*  Powered by crackmes.one  *");
    puts("\t*      Difficulty : 3.0     *");
    puts("\t*****************************\n");
}

int _strcmpKey(const char *string1, const char *string2)
{
    int is_equals = 1; // there two trings are equals as default
    int n = _strlen(string1),
        m = _strlen(string2);

    if(n == m){
        for(int i=0; i < n; i++){
            if(string1[i] != string2[i]){
                is_equals = 0;
                return is_equals;
            }
        }
    }else is_equals=0;

    return is_equals;
}

char *getEncrytKey(const char *uName)
{
    char *key = "tryHarderToMakeAGoodKeyGen";
    int l = _strlen(key),
        n = _strlen(uName);
    char *goodSerial = (char *)malloc(sizeof(char) * n);
    
    if(goodSerial == NULL)
        ExitWithError("Erreur d'allocation dynamique");

    for(int i=0, j=0; i<n; i++){
        j = ((int)uName[i] ^ l) % n;
        goodSerial[i] = uName[j];
    }

    return goodSerial;
}

void ExitWithError(const char *message)
{
    fprintf(stderr, "%s \n", message);
    exit(EXIT_FAILURE);
}

void clearBuffer(char *buffer)
{
    int i=0;
    while((buffer[i] = getchar()) != '\n'){
        i++;
    }
}

int _strlen(const char *string)
{
    int size = 0;
    for(int i=0; string[i] != '\0'; i++)
        size++;
    
    return size;
}

void printRules(void)
{
    puts("Hi cracker and welcome on this keygenme maked by @Danofred\n");
    puts("RULES :");
    puts("\t- Don't patch this program");
    puts("\t- Try to make a keygen");
    puts("\n\t\t:) Good Luck");
}