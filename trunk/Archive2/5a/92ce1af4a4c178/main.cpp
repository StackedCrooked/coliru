/*********************************
* Class: MAGSHIMIM C1    		 *
* Week 2           				 *
* HW solution 12	  			 *
* Postfix/Prefix				 *
**********************************/

#include <stdlib.h>
#include <stdio.h>

/**
What does the program print?

Input:
	None
Output:
	The program returns 0 upon successful completion of its running
*/
int main()
{
	int a = 97;
	int b;

	b = a-- + a-- + 1;						// a = 95, b = 97 + 97 + 1 = 195
	printf("a1 = %d, b1 = %d\n", a, b);		// "a1 = 95, b1 = 195"

	a = 23;									// a = 23
	a *= 2;									// a = 46
	b = --a + --a + 1;						// a = 44, b = 44 + 44 + 1 = 89
	printf("a2 = %d, b2 = %d\n", a, b);		// "a2 = 44, b2 = 89"
	return (0);
}
