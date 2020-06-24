/*
 *
 *	Project:	Homework Assignment #1
 *	Program:	russe10.c
 *	Location:	/jhu/406/russe10.c
 *	Description Russe is a variation of the multiplication algorithm
 *				used in computers the algorithm comes directly
 *				from "Fund. of Algorithms," by B&B
 *			- Russe4 adds post-conditions
 *			- Russe5 cycles thru "K" iterations(tests)
 *			- Russe9 adds "I" & "J" to facilitate loop invariant
 *			- Russe10 adds triangular profiles and Print_Levels
 *
 *	Programmer:	JD Durick
 *	System:		Tested on a Linux box (2 types of distributions:  FreeBSD 3.3 & Red Hat 6.1 - 2.0.36)
 *	Date Created:	02/21/00
 *
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define LARGEST_MorN 200
#define subrange1mil 40000

int truncate(int var);
int get_rand_number();
int Result2(int m, int n);
void get_out();

int main(void) {

	//variable declarations

	int oracle, answer, iterations, j, m0, n0, failures, print_level;

	double get_rel = 0.0; //holds reliability value
	char cr;
	char wait; //waits for key to be pressed

	srand(time(NULL)); //sets the random seed
	system("cls"); //clears the screen
	failures = 0; //set failures to zero
	print_level = 1; //set print_level to 1

	//prompt the user for iterations

	printf("How many iterations (tests of Russe)? ");
	scanf("%d%c", &iterations, &cr); //reads in iteration number
	printf("\n");

	for (j = 0; j < iterations; j++) //loops through iterations
			{

		m0 = get_rand_number(); //gets return value of get_rand_number
		n0 = get_rand_number(); //gets return value of get_rand_number

		if (print_level == 1) //print if one
				{
			printf("%4d\t%4d\t===>\t%d\n", m0, n0, m0 * n0);
		}

		if (m0 < 0 || n0 < 0) //if values are above zero
				{
			printf("assertion error, M0 * N0 => %d\n", subrange1mil);
			printf("Press enter to return to the program");
			wait = getchar();
			get_out(); //exits out of program
		}

		answer = Result2(m0, n0); //gets return value from Result2
		oracle = m0 * n0; //holds multiplication value of m0 and n0

		if (oracle > subrange1mil) {
			printf("%d - Oracle number is out of range\n", oracle);
			get_out();
		} //end of if 											//statement

		if (answer != oracle) {
			printf(
					"Russe yields ANSWER = %d ... Check it against ORACLE = %d\n",
					answer, oracle);
			failures++;
			get_rel = 1 - (failures / iterations);
			printf("# of failures = %d ... Estimated SW Reliablity = %f\n",
					failures, get_rel);
			printf(
					"============================================================================\n");
		} //end of if statement

	} //end of for loop

	get_rel = 1 - (failures / iterations);
	printf("\nFinal # of failures = %d;\tFinal SW Reliablity = %f\n", failures,
			get_rel);
	printf("--------------------------------------------------------------\n");
	printf("This completes the calculations and screen print!\n");
	printf("Press enter to return to the program.\n");
	wait = getchar();
	get_out();
}

void get_out() //exits out of program
{

	exit(EXIT_SUCCESS);

}

int truncate(int var) {

	return (var);

} //end of truncate function

int get_rand_number() //finds the random numbers
{

	//Declaration of local variables for get_rand_number

	double test_sqrt = 0.0;
	double sqrt_result = 0;
	float x = 0.0;
	int x0 = 0;
	int rand_number = 0;

	rand_number = rand();
	test_sqrt = sqrt(abs(1 - rand_number));
	sqrt_result = test_sqrt - (int) test_sqrt; //range from 0 - 1

	x = LARGEST_MorN * (1 - sqrt_result); //gets 200 * (some value between 0 and 1)
	x0 = truncate(x);

	if (x0 < 0 || x0 > subrange1mil) {
		printf("%d - Number out of subrange\n", x0);
		get_out(); //exits out
	}
	return (x0);

}

int Result2(int m, int n) {
	int result, i, j;

	result = 0;
	i = 0;
	j = 0;

	if (m > 0 && m <= LARGEST_MorN && n > 0 && n <= LARGEST_MorN) {
		do {
			if ((m % 2) == 1) {
				result = result + n;
				i++;
			}
			j++;

			m = m / 2;
			n = n + n;
		} while (m != 0);
	}

	return (result);

}

