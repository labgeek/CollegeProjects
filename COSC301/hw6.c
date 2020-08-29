/*****************************************************************//**
 * \file   hw6.c
 * \brief  Counts the number of words of a given length in maxRow sentences
 * 
 * \author JD Durick
 * \date   4/10/1996
 *********************************************************************/

#include <stdio.h>
#include <string.h>

#define maxCol 81
#define maxRow 1

/**
 * Function prototypes.
 */
int PrintInstr();
int GetSentence(int, int*);
void PrintOutput(int, int*);
int countwordlen(char*, int*, int);

/**
 * Main driver program
 * Description:  Prints instructions, reads line to calculate word occurrence 
 * frequency, then prints it back out..
 * \return 
 */
int main()
{
	int longestword = 0;
	int wordlength[maxCol] = { 0 };
	PrintInstr();

	for (int count = 0; count < maxRow; count++)
		longestword = GetSentence(longestword, wordlength);

	PrintOutput(longestword, wordlength);
	return 0;
}

/**
 * Prints instructions.
 * 
 * \return 
 */
int PrintInstr(void) {
	printf("You will enter %d sentences.", maxRow);
	printf("Each with a max of %d characters.\n\n", maxCol - 1);
	printf("The program will give you a total number of words of a given length found in the sentence.\n");
	return 0;

}

int GetSentence(int longest, int* wdlength) {

	char sentence[maxCol];
	char* token = NULL;
	int length = 0;

	printf("Please enter a sentence not more than %d characters (enter below)\n\n", maxCol - 1);
	fgets(sentence, sizeof sentence, stdin);
	printf("\n\n");
	token = strtok(sentence, " ");

	while (token != NULL) {
		longest = countwordlen(token, wdlength, longest);
		token = strtok(NULL, " ");
	}
	return longest;
}

int countwordlen(char* wptr, int* wlen, int islongest) {
	char* punct = ",.?!:;\n";
	int length = 0;
	
	length = strcspn(wptr, punct);
	printf("Length = %d\n", length);
	if (length > islongest)
		islongest = length;
	wlen[length]++;
	return islongest;
}

void PrintOutput(int printlines, int* wordlenarray) {
	int count = 0;
	printf("WORD LENGTH     |   WORD COUNT\n");
	printf("------------------------------\n");

	for (count = 1; count <= printlines; count++)
		printf("%5d %14d\n", count, wordlenarray[count]);

	printf("\n\n");
	return;
}
