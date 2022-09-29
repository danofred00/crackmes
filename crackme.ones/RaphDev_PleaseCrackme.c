/*
	Powered by crackmes.one
	This is a keygen for RaphDev's Crackme called PleaseCackme
	source: https://crackmes.one/crackme/612e85d833c5d41acedffa4f
	@author Danofred
*/

#include <stdio.h>
#include <string.h>

// the buffer's size for username, entry_password and 
// great_password is 32 bytes

#define STR_LEN 32

int main(int argc, char const *argv[])
{

	char username[STR_LEN];
	char password[STR_LEN];
	char greatPassword[STR_LEN];
	int num_entry;

	// getting username
	printf("%s\n", "Enter your username :");
	scanf("%s", username);


	printf("%s\n", "Choose any number between 0 and 9 :");
	scanf("%d", &num_entry);

	if (num_entry < 0)
	{
		printf("%s\n", "Number is too small");
	} else if (num_entry > 9) {
		printf("%s\n", "Number is too big");
	} else {

		// here is generatePassword method
		for (int i = 0; i < strlen(username); ++i)
		{
			greatPassword[i] = username[i] + num_entry;
		}

		printf("Your password is : %s\n", greatPassword);
	}

	return 0;
}
