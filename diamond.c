/*
 * diamond.c
 *
 *  Created on: 2/19/1996
 *      Author: JD Durick
 *      gcc -o diamond diamond.c
 */


#include <stdio.h>

int main()
{
	int row, col, space, num, maxnum;
	maxnum=19;

	printf("Please enter an odd integer between 1-19:");
	scanf("%d", &num);

	while((num < 1) || (num>19) || (num %2==0)){
		printf("Sorry, Please enter an odd integer between 1-19:");
		scanf("%d", &num);
	}

	for(row=1; row<=num; row+=2){
		for(space=1; space <=(num-row)/2; space++)
			printf(" ");

		for(col=1; col<=row;col++)
			printf("*");

		printf("\n");

	}

	for(row=num-2; row>=1; row-=2){
		for(space=(num-row)/2; space>=1; space--)
			printf(" ");

		for(col=row;col>=1; col--)
			printf("*");

		printf("\n");


	}
	return 0;

}

/*
 * root@taffy:/home/jd/projects/Classroom_code# ./diamond
Please enter an odd integer between 1-19:19
         *
        ***
       *****
      *******
     *********
    ***********
   *************
  ***************
 *****************
*******************
 *****************
  ***************
   *************
    ***********
     *********
      *******
       *****
        ***
         *
 *
 */

