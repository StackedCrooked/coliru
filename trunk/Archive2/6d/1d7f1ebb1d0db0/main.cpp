// array of structures
#include <iostream>
/*
 * program to compute a factorial
 * invocation:
 *    fact		run it
 * exit code: 0 always
 * author: Matt Bishop, bishop@cs.ucdavis.edu, 9/16/96
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * compute a single-precision factorial
 */
int fact(int n)
{
	/*
	 * the two terminal cases
	 */
	/* sanity check */
	if (n < 0)	return(-1);
	/* here's the end */
	if (n == 0)	return(1);
	/*
	 * if it isn't those, recurse
	 */
	return(n * fact(n-1));
}

/*
 * the main program
 */
int main(void)
{
	int n;			/* number to compute factorial of */
	register int nread;	/* number of numbers read */

	/*
	 * read numbers and compute their factorial
	 */
	while(printf("> "), (nread = scanf("%d", &n)) != EOF){
		switch(nread){
		case 0:		/* bad input */
			printf("Need a non-negative integer\n");
			break;
		case 1:		/* good input */
			printf("\t%d\n", fact(n));
			break;
		default:	/* can't happen (uh huh ...) */
			printf("HUH? nread = %d?!?!\n", nread);
			break;
		}
	}

	/*
	 * skip to a new line and quit
	 */
	putchar('\n');
	return(EXIT_SUCCESS);
}
	
    