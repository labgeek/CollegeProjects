/**
Author:  JD Durick
Assignement #2: Homework #2 CS 605.402
Due Date:  6/28/99
Abstract:  To write a program that read an english language
phrase into Morse code.  Also write Morse code to english!
Instructor:  Doug Ferguson
Program:  Morse.cc
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable : 4996)
using namespace std;

const int the_size = 38;

const char* morse[the_size] = { ".-", "-...", "-.-.", "-..",".", "..-.", "--.", "....", "..", ".---",
				   "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
				   "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--",
				   "....-", ".....", "-....", "--...", "---..", "----.", "-----", " ",
				   " " };
const char* characters[the_size] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
					"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
					"U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4",
					"5", "6", "7", "8", "9", "0", "  ", "*" };
/**
Function Prototypes
*/
void to_morse(void);
int linear_search(const char* [], char, int);
int string_search(const char* [], char*, int);
void to_alpha(void);

int main()
{
	to_morse();
	to_alpha();
	//cout << endl;
	return 0;
}

void to_alpha(void){
	char *phrasePtr;
	int	space = 0;
	char alpha_phrase[80];
	int	cell;
	int	i = 0;
	int	j = 0;
	char phrase[80];

	cout << endl << "Please enter a phrase in Morse Code: ";
	cin.getline(phrase, 80, '\n');
	for(i = 0; i < 80; ++i)
	{
		if(phrase[i] != '\n')
		{
			if(phrase[i] == ' ' && phrase[i+1] == ' ' && phrase[i+2] == ' ')
			{
				phrase[i+1] = '*';
				if((i+2) < 80)
					i+=2;
				else
					i=80;

			}
		}
	}

	cout << endl << "The phrase you entered is: " << phrase<< endl;
	cout  << "The English phrase that has been converted into Morse code is: ";

	phrasePtr = strtok(phrase, " ");
	while(phrasePtr != NULL)
	{
		cell = string_search(morse, phrasePtr,the_size);
		alpha_phrase[j] = *characters[cell];
		++j;
		phrasePtr = strtok(NULL, " ");
	}

	alpha_phrase[j] = '\0';
	cout << alpha_phrase << endl;

}

void to_morse(void) {
	int cell;
	int length;
	char letter;
	char phrase[80];

	cout << "Please enter an English phrase: "  << endl;
	cin.getline(phrase, 80);
	length = (strlen(phrase));

	for (int i = 0; i < length; i++)
	{
		if (islower(phrase[i]))
			letter = toupper(phrase[i]);
		else
			letter = phrase[i];

		cell = linear_search(characters, letter, the_size);
		cout << morse[cell];
	}
}

int linear_search(const char* array[], char key, int sizeOfArray)
{
	int n;
	for (n = 0; n < sizeOfArray; n++)
	{
		if (*array[n] == key)
			return n;
	}
	return -1;
}


int string_search(const char* array[], char* element, int sizeOfArray)
{
	int n;
	for (n = 0; n < sizeOfArray; n++) {
		if (!strcmp(element, array[n])){
		return n;
		}
	}
	return -1;
}
