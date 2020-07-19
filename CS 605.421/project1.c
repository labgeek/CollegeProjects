//SECTION II
//  DATA ANALYSIS PROGRAM USING MERGESORT AND QUICK SORTS PARTITION FUNCTION
//                              (Source Code)

//*****************************************************
// AUTHOR:      JD DURICK                       
//                                                    
//	Assignment:  Programming Assignment #1; CS 605.421 
//					 Foundations of Algorithms in C++      
//					 Dr. John Sadowsky                     
//                                                    
//	Abstract: 	 To implement two methods (Merge sort  
//					 and Quick sort) for finding a median  
//					 of a random set of numbers.  Also,    
//					 compare the run time performance of   
//					 both algorithms with each other on    
//					 randomly generated input sets as the  
//					 size of the input data increases over 
//					 at least four powers of ten.          
//                                                    
// Due Date:	 Wednesday, 03/11/98                   
//                                                    
//	FILE:        SORT.C:  Program that sorts the items 
//                       in an array into ascending   
//                       order.                       
//                                                    
//*****************************************************

/**
 * @author JD Durick
 * @date 3/11/1998
 * Assignment:  To implement two methods (Merge sort and Quick Sort
 * for finding a median of random set of numbers.  Also, compare
 * the run time performance of both algorithms with each other on
 * randomly generated input sets as the size of the input increases
 * over at least four powers of 10.
 */

const int YES = 1; //constant variable set to 1
const int NO = 0; //constant variable set to 0

#include <stdio.h>             			//header file for input/output
#include <time.h>                     	//header file for computing run time
#include <stdlib.h>						//for the rand function
#include <ctype.h>						//used for tolower() function

#define max_loop 500 //# of for loops for sort comparison
#define row 20 //puts numbers in rows of 20
#define cent 100 //used with random function (0-99)
#define min_loop 50 //used with calculating when n = 1001
#define modeMax 100 //global variable for frequency array
#define MAX 11 //global variable set for the number of
//elements in the array
#define half 2 //global variable that sets 2 to half

int select(void); //function to allow you to pick merge or
//quick sort
int instructions(void); //prints instructions for user interface
char go_again(void); //function to allow user to conduct
//another sort
int continue_function(void); //function that allows the user to
//continue with program
void MergeSort(int a[MAX], int, int); //sorts array into ascending order using
//merge sort
void Merge(int a[], int, int, int); //merges to sorted array segments
void median_merge(int a[MAX]); //finds the median before the array is
//sorted(for the merge sort)
void median_after(int a[MAX]); //finds the median after the array is
//sorted
void mean(int a[MAX]); //finds mean in array set
void inversion(int a[MAX]); //calculates the number of inversions
//in a data set
void random_array(int a[MAX]); //puts random numbers in the array
void print_array(int a[MAX]); //print element of  the array into rows
//of 20
void error(void); //produces error message
void goodbye(void); //exits the program
void quicksort(int a[MAX], int, int); //function to split array, using a
//pivot value puting everything less
//to the left, everything greater to
//the right
void swap(int a[MAX], int*, int*); //swaps values for quicksort function
void test_sort(int a[MAX]); //function to test whether sorted array
//is actualy sorted or not
void get_time(int a[MAX]); //gets the time of the sorts and show you
//the sorted arrays
void user_instruct(void); //function to allow user to see
//instructions as opposed to just written
//to a file

FILE *fptr;

void main(void) //main function
{

	//Declaration of variables

	int a[MAX]; //holds the array of element
	int my_choice; //holds menu selection variable
	char resp; //holds character value
	int cont; //holds "continue" value

	fptr = fopen("file.dat", "w"); //creates a file named "test.dat" to be
	//written to, if file already exists,
	//discard the current contents

	if (fptr == NULL) //if pointer variable point to NULL
		printf("ERROR\n"); //then produce error message

	else //else, continue with program
	{
		srand(time(NULL)); //produce different sequence of random
		//numbers each run
		user_instruct(); //function to allow user to see
		//instructions as opposed to just written
		//to a file

		cont = instructions(); //function that instructions returns
		//is assigned to cont
		if (cont == YES) //if cont is true(1)
				{

			do //beginning of do/while loop
			{
				my_choice = select(); //function select assigns return value
				//to my_choice

				switch (my_choice) //beginning of switch statement
				{
				case (1): {
					printf("SORTING STARTED...\n\n\n\n");
					fprintf(fptr, "(A).  Our DATA SET contains %d elements.\n",
							MAX);
					fprintf(fptr,
							"(B).  Here are the UNSORTED numbers for both SORTS:\n");

					get_time(a); //gets the time of the sorts and show you
					//the sorted arrays

					fprintf(fptr, "\n(G).  DATA ANALYSIS:\n");
					mean(a); //finds mean of the array
					median_after(a); //finds median element(s) in array, depend
					//on even or odd data set
					printf("SORTING FINISHED...\n");
					printf(
							"Your sorting comparison data has been written to a file\n");
					printf("called file.dat.\n");
					resp = go_again(); //function to ask user to continue or not
					break; //break out of loop
				}

				default: //if 1 was not selected,
					//default is executed
				{
					goodbye(); //exits the program
					return;
				}
				} //end of switch

				fclose(fptr); //closes test.dat for writing

			} while (tolower(resp) != 'q'); //end of do / while loop
		} //end of if statement
		else
			goodbye(); //exits the program
		return;

	} //end of else

	goodbye(); //exits the program
	return;

} //end of main function
//BEGINNING OF SUBPROCEDURES

void random_array(int a[MAX]) //selects randoms numbers to be printed
{

	int ctr; //counter
	for (ctr = 0; ctr < MAX; ctr++) {
		a[ctr] = (rand() % cent); //selects number between 0 and 99

	}
	return;
}

void print_array(int a[MAX]) //prints array of numbers
{
	int ctr; //counter variable
	for (ctr = 0; ctr < MAX; ctr++) {
		if (ctr % row == 0) //everytime counter equals a number
				//that is mod 20 and produces a
				//0, it puts numbers in rows of 20
				{
			fprintf(fptr, "\n", a[ctr]);
		}
		fprintf(fptr, "%3d", a[ctr]); //prints out numbers in rows of 20
	}
} //end of print_array function

void error(void) //prints out error message
{
	printf("***** ERROR *****\n");
	printf("You file could not be opened.\n");
	return;
} //end of error function

void goodbye(void) //exits the program with friendly message
{
	printf("\nThank you for using the program and GOODBYE.\n");
	fprintf(fptr, "\nThank you for using the program and GOODBYE.\n");
	return;
}

void median_after(int a[MAX]) //finds median element of array
{

	if (MAX % half == 1) //condition is always true unless
			//you change MAX
			{
		fprintf(fptr, "\n\n*MEDIAN (after the array is sorted) is %d.\n",
				a[MAX / half]);
	} else {
		fprintf(fptr,
				"The median is element %d and %d of the sorted %d element array.\n",
				MAX / 2, (MAX / 2) + 1, MAX);
		fprintf(fptr, "For this run, the median is %d and %d.\n",
				(a[MAX / half - 1]), a[MAX / 2]);
	}
}

void inversion(int a[MAX]) //function that counts the number of inversions in a data set
{
	//local variables

	int a1 = 1, //counter
			b1 = 1, //counter
			ara1 = 0, //first array position a[0]
			ara2 = 1; //second array position a[1]
	long double z = 0; //used long to hold bigger value

	//brute-force method of search for # of inversions

	while (a1 < MAX) //while a1 is always less than total elements
	{
		while (b1 <= MAX) //go through whole array
		{
			if (a[ara1] > a[ara2]) //if first element is greater than second
				z++; //then, increment our counter z
			if (ara2 < MAX - 1) //if the second element is less than the
			//the total number of elements minus 1
				ara2++; //then increment second array position
			else
				break; //else, break out of loop
		}
		ara1++; //increment first array position
		ara2 = ara1; //copy ara1 to ara2
		ara2++; //then increment second array position
		a1++; //increment a1 counter
		b1 = a1; //copy a1 to b1
	}

	if (z == 0) //if number of inversions equals 0, then
			//array is already sorted.
			{
		fprintf(fptr,"     *NUMBER OF INVERSION(S) (before sort) in %d element array:  %.1Lf\n",MAX, z);

	}

	if (z >= 1) //if its greater than or equals one, array
		//was not sorted when first began.
		fprintf(fptr,
				"     *NUMBER OF INVERSION(S) (before sort) in %d element array:  %.1Lf.\n",
				MAX, z);

} //end of inversion function

//*******************************************************
// MergeSort: Sorts the items in an array into          *
//            ascending order.                          *
//                                                      *
// PRE:   a[f..l] is an array                           *
// POST:  a[f..l] is sorted in ascending order          *
// CALLS: Merge                                         *
//                                                      *
// APPROACH: Recursively calls itself on two halves of  *
//           the list. Base case is two items that can  *
//           be compared directly, or a single item     *
//           which is sorted already. The two sorted    *
//           halves must be merged together.            *
//                                                      *
// VARIABLES: int mid - index of midpoint               *
//                                                      *
//*******************************************************

void MergeSort(int a[MAX], int f, int l) //sorts items in array into
//ascending order
{
	int mid; //index of midpoint

	if (f < l) {
		mid = (f + l) / half; //finds midpoint of array
		MergeSort(a, f, mid); //MergeSort recursively calls
		//itself
		MergeSort(a, mid + 1, l); //MergeSort recursively calls
		//itself
		Merge(a, f, mid, l); //call to Merge function
		//(combining arrays)
	}

	return;
}

//*******************************************************
// Merge: Merges two sorted array segments a[f..mid]    *
//        and a[mid + 1..l] into one sorted array.      *
//                                                      *
// PRE:   f <= mid <= l. The subarrays a[f..mid] and    *
//        a[mid + 1..l] are each sorted in increasing   *
//        order.                                        *
// POST:  a[f..l] is sorted.                            *
//                                                      *
// LOCAL: INT      tempArray[MAXSZ] - temporary array   *
//        int      first1           - start of subarray1*
//        int      last1            - end of subarray1  *
//        int      first2           - start of subarray2*
//        int      last2            - end of subarray2  *
//        int      index            - next temp free pos*
//                                                      *
// APPROACH: Copy the smaller item at index i into the  *
//           temporary array. When done, copy the rest  *
//           of the remaining array into the temporary  *
//           array, then transfer all back to a         *
//                                                      *
// INVARIANT: tempArray[first1..index - 1] is in order  *
//                                                      *
// IMPLEMENTATION NOTE: This function merges the two    *
//                      subarrays into a temporary array*
//                      and copies the result into the  *
//                      original array a.               *
//                                                      *
//*******************************************************

void Merge(int a[MAX], int f, int mid, int l) //merges two sorted array
//segments
{
	//declare local variables

	int tempArray[MAX]; //temporary array
	int first1 = f; //assign value of f to first
	int last1 = mid; //assign mid to last1
	int first2 = mid + 1; //assign mid+1 to first 2
	int last2 = l; //assign l to last2
	int index = 0; //variable index

	for (index = first1; (first1 <= last1) && (first2 <= last2); index++) {
		if (a[first1] < a[first2]) //if first element is less than
				//second element
				{
			tempArray[index] = a[first1]; //copy first element into
			//tempArray
			first1++; //increment first1 counter
		} else {
			tempArray[index] = a[first2]; //copy second element into
			//tempArray
			first2++; //increment second counter
		}
	} //end of for loop

	for (index; first1 <= last1; first1++, index++)
		tempArray[index] = a[first1]; //put first element into tempArray

	for (index; first2 <= last2; first2++, index++)
		tempArray[index] = a[first2]; //put second element into tempArray

	for (index = f; index <= l; index++)
		a[index] = tempArray[index]; //copy temporary array to original

	return;
}

void test_sort(int a[]) //function to test the validity of the
//sort
{
	//local variables

	int a1 = 1, //counter
			b1 = 1, //counter
			ara1 = 0, //first array position a[0]
			ara2 = 1; //second array position a[1]
	long double z = 0; //used long to hold bigger value

	//brute-force method of search for # of inversions

	while (a1 < MAX) //while a1 is always less than total elements
	{
		while (b1 <= MAX) //go through whole array
		{
			if (a[ara1] > a[ara2]) //if first element is greater than second
				z++; //then, increment our counter z
			if (ara2 < MAX - 1) //if the second element is less than the
			//the total number of elements minus 1
				ara2++; //then increment second array position
			else
				break; //else, break out of loop
		}
		ara1++; //increment first array position
		ara2 = ara1; //copy ara1 to ara2
		ara2++; //then increment second array position
		a1++; //increment a1 counter
		b1 = a1; //copy a1 to b1
	}

	if (z == 0) //if z equal 0, then your algorithm is a
			//success
			{
		fprintf(fptr, "*NUMBER OF INVERSION(S) (after sort): %d\n", z);

	} else
		//if its anything but 0, there was a
		//problem with your algorithm
		fprintf(fptr, "*NUMBER OF INVERSION(S) (after sort): %d\n", z);

} //end of test_sort program

int instructions(void) //function that prints the instructions
{

	int cont;
	fprintf(fptr,
			"Welcome to the Merge sort / Quick Sorts Partitioning Analysis program.\n");
	fprintf(fptr,
			"**********************************************************************\n\n");
	fprintf(fptr,
			"This program implements two methods (Merge sort and Quick sort) for\n");
	fprintf(fptr,
			"finding a median random numbers.  Also, the program will compare the run \n");
	fprintf(fptr,
			"time performance of both algorithms with each other on randomly generated\n");
	fprintf(fptr,
			"input sets as the size of the input data set increases over at least\n");
	fprintf(fptr,
			"four powers of ten.  In addition, the partition function from Quick\n");
	fprintf(fptr,
			"Sort is used to find the median with partial, but not complete sorting\n\n");
	fprintf(fptr, "                           MENU\n");
	fprintf(fptr, "                *************************** \n");
	fprintf(fptr,
			"	1.  Compare the MERGE SORT vs. QUICK SORTS PARTITIONING algorithm.\n");
	fprintf(fptr, "	2.  Quit the program\n\n");

	cont = continue_function();

	return (cont);
} //end of instructions function

int continue_function(void) //function that allows you to continue
//or not
{
	char x; //holds "continue" value

	printf("Do you wish to continue? (Q = Quit / C = Continue)\n");
	scanf(" %c", &x);
	//while value is not a 'c' or 'q', you
	//must go again until enter correct
	//respons
	while ((tolower(x) != 'c') && (tolower(x) != 'q')) {
		printf("You have entered an INVALID key.\n");
		printf("Please enter Q to Quit or C to Continue.\n");
		scanf(" %c", &x);
	}

	if (tolower(x) == 'q') //if your value is 'q', then it
		//returns a 0
		return (NO);
	else
		//else, returns a true(1)
		return (YES);
} //end of continue_function

int select(void) //function that allows you to select menu option
{
	int choice; //holds selection value
	printf("\nPlease make a selection now: \n");
	scanf(" %d", &choice); //reads that value in
	printf("\n");

	return (choice); //returns choice value
} //end of select function

char go_again(void) //function that prompts you to go again
{
	char response; //holds response value

	printf("\nWould you like do another comparison? (C or Q)\n");
	scanf(" %c", &response);

	if (tolower(response == 'q')) //if response is q, call goodbye function
		goodbye();

	while ((tolower(response) != 'c') && (tolower(response) != 'q')) {
		printf("You have entered an INVALID key.\n");
		printf("Please enter Q to Quit or C to Continue.\n");
		scanf(" %c", &response);

	}
	return (response); //return value response
} //end of go_again function

//******************************************************
// QuickSort: Sorts the items in an array into         *
//            ascending order.                         *
//                                                     *
// PRE:   a[l..l] is an array                          *
// POST:  a[l..l] is sorted in ascending order         *
//                                                     *
// APPROACH: Partitions the list and then recursively  *
//           calls itself on two parts of the list.    *
//           Base case is two items that can be        *
//           compared directly, or a single item which *
//           is sorted already.                        *
//                                                     *
//******************************************************

void quicksort(int a[], int l, int r) //function to split array, using a
//pivot value puting everything less
//to the left, everything greater to
//the right
{
	int i, j; //left and right scan pointers
	int v; //holds current value of partitioning
	//element a[r]
	if (r > l) //
			{
		v = a[r]; //setting current value to a[r]
		i = l - 1; //assigning i left side
		j = r; //assigning j right side

		for (;;) //For the whole section, put
				//everything less than the pivot (j)
				//to the left, and greater than the
				//pivot to the right
				{
			while (a[++i] < v)
				; //while less than current value,
			//increment left scan pointer
			while (a[--j] > v)
				; //while greater than current value,
			//decrement right scan pointer
			if (i >= j)
				break; //when pointers cross
			swap(a, &i, &j);
			//call to swap function
		}
		swap(a, &i, &r); //call to swap function

		print_array(a);

		quicksort(a, l, i - 1); // sort the left side
		quicksort(a, i + 1, r); // sort the right side
	}
} //end of quicksort function

void swap(int a[], int *l, int *r) //swaps values for quicksort
{
	int i = a[*l]; //if pair is not in order
	a[*l] = a[*r];
	a[*r] = i; //swap here
	return;
} //end of swap function

void mean(int a[MAX]) //finds mean of sorted array
{
	int j;
	long double total = 0;

	fprintf(fptr, "\n               ********* MEAN *********\n");
	for (j = 0; j <= MAX - 1; j++)
		total += a[j];

	fprintf(fptr,
			"The mean is the average value of the data items.  The mean is equal\n");
	fprintf(fptr,
			"to the total of all the data items divided by the number of data items (%d).\n",
			MAX);
	fprintf(fptr, "The mean value for this run is %.1Lf /%d = %.2Lf.\n\n",
			total, MAX, (long double) total / MAX);

	return;
} //end of mean function

void median_merge(int a[MAX]) //finds median element of array
{

	if (MAX % half == 1) {
		fprintf(fptr,
				"     *MEDIAN (before the array is sorted) of array size %d is: %d\n",
				MAX, a[MAX / 2]);
	} else {
		fprintf(fptr,
				"The median is element %d and %d of the sorted %d element array.\n",
				MAX / 2, (MAX / 2) + 1, MAX);
		fprintf(fptr, "For this run, the median is %d and %d.\n",
				(a[MAX / 2 - 1]), a[MAX / 2]);
	}
} //end of median_before function

void get_time(int a[MAX]) {
	int ctr, i; //counter variable
	clock_t start, end; //initializes timer variables
	int loop = max_loop; //for loop to counter act the fast speed
	//of the Pentium processor
	int loop2 = min_loop; //for loop used when n = 1001
	int b[MAX];

	random_array(a); //produces randoms numbers
	for (ctr = 0; ctr <= MAX - 1; ctr++)
		b[ctr] = a[ctr];
	print_array(a); //prints UNSORTED numbers
	fprintf(fptr, "\n\nMERGE SORT ANALYSIS of RANDOM DATA SET:\n");
	median_merge(a); //gets the median before the array is sorted
	inversion(a); //counts number of inversions
	fprintf(fptr, "\n\n(E).  MERGE SORT: \n");
	start = clock(); //starts the time

	for (ctr = 1; ctr <= 1; ctr++) //for loop to counter act the fast speed
			//of the Pentium processor
			{
		MergeSort(a, 0, MAX - 1); //sorts the array into ascending order
	}
	end = clock(); //end of timer
	fprintf(fptr, "		*Time Started: %.3f\n", start / CLK_TCK);
	fprintf(fptr, "		*Time Ended:  %.3f\n", end / CLK_TCK);
	fprintf(fptr, "		*Total time during Merge Sort run: %.3f\n\n",
			(end - start) / CLK_TCK);
	fprintf(fptr, "\n(F).  Here are the sorted numbers using MERGE SORT:\n");
	print_array(a); //prints SORTED numbers
	median_after(a); //finds median element(s) in array, depend
	//on even or odd data set
	test_sort(a); //tests whether array is correctly sorted

	fprintf(fptr, "\n(C).  FINDING THE PARTITIONING ELEMENT:  \n");
	start = clock(); //starts the time

	for (i = 0; i < MAX; i++)
		a[i] = b[i];

	//	random_array(b);
	for (ctr = 1; ctr <= 1; ctr++) //for loop to counter act the fast speed
			//of the Pentium processor
			{
		quicksort(a, 0, MAX - 1); //sorts array using quick sort algorithm
	}
	end = clock(); //end of timer

	fprintf(fptr, "\n\n		*Time Started: %.3f\n", start / CLK_TCK);
	fprintf(fptr, "		*Time Ended:  %.3f\n", end / CLK_TCK);
	fprintf(fptr, "		*Total time it took to find the Partition element: %.3f\n",
			(end - start) / CLK_TCK);
	fprintf(fptr, "\n\n(D).  The median is element %d of %d elements:\n",
			MAX / 2 + 1, MAX);
	fprintf(fptr, "\nFor this run, the median is %d\n", a[MAX / 2]);
	print_array(a); //prints array after median is found
	median_after(a); //finds median element(s) in array, depend
	//on even or odd data set
	test_sort(a); //tests whether array is correctly sorted
	return;
}

void user_instruct(void) //user_instruct funtion used for friendly user interface
{
	printf("Welcome to the Merge sort / Quick Sort Analysis program.\n");
	printf("********************************************************\n\n");
	printf("This program implements two methods (Merge sort and Quick sorts\n");
	printf(
			"partitioning algorithm) for finding a median random numbers.  Also,\n");
	printf(
			"the program will compare the run time performance of both algorithms\n");
	printf(
			"with each other on randomly generated input sets as the size of the\n");
	printf("input data set increases over at least\n four powers of ten.\n\n");
	printf("                           MENU\n");
	printf("                *************************** \n");
	printf(
			"	1.  Compare the MERGE SORT vs. QUICK sorts Partitioning algorithm.\n");
	printf("	2.  Quit the program\n\n");

	return;
} //end of user_instruct function
