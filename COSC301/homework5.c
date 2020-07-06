/*
*	COSC 301	Spr. 1996	D. Cheslock
*	Project: Home Assignment #5
*	Author: JD Durick
*	File: /usr/class/prob13/five.c
*	Date: 03/28/96
*	Abstract: homework 5 - assignment will use array of pointers to characters.  Each
*	pointer will point to string and the pointers are to be sorted.
*	Revision History:	Date	Who	Description
03/28/96	Initial Release
*/


#include <stdio.h>
#include <string.h>

#define sizeArray 12

int sort_array(char *name[sizeArray]);
int print_array(char *a[sizeArray]);


int main(){

	int i;;
	char *name[sizeArray] = {
			{"This"},
			{"is"},
			{"the"},
			{"TEST"},
			{"sentence"},
			{"that"},
			{"is"},
			{"to"},
			{"be"},
			{"used"},
			{"for"},
			{"ha5"},
	};

	printf("\nThe original array of pointers to characters:  \n");
	print_array(name);
	sort_array(name);
	printf("\nThe sorted array of pointers to characters:  \n");
	print_array(name);
	return 0;
}


int sort_array (char *a[sizeArray]){

	int i, exchanges;
	char *temp;

	do
	{
		exchanges = 0;
		for(i = 0; i<(sizeArray -1); i++)
		{
			if(strcmp(a[i], a[i + 1]) > 0)
			{
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				exchanges = 1;
			}
		}

	}while(exchanges == 1);
	return 0;
}


int print_array(char *a[sizeArray])
{
	int counter;
	printf("\n");
	for(counter = 0; counter < sizeArray; counter++)
	{
		printf("Element[%d] = \"%s\"\n", (counter), *(a+counter));
	}

	return 0;

}

