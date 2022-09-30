
/*
	this is a simple c crackme coded ny MrEmpy
	MrEmpty's Crackme : tryhackme
	link : https://crackmes.one/crackme/61c8deff33c5d413767ca0ea
	@author Danofred
	https://crackmes.one
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	// this is a key in str format
	char str[] = "4@ss724536";
	char key[103];

	for (int i = 0,j=0; i < strlen(str); ++i,j=j+2)
	{
		//key[i] = str[i] + j;
		// the key is str in hexadecimal format
		sprintf((key+j),"%02x", str[i]);
	}

	printf("Your key : %s\n",key);

	return 0;
}
