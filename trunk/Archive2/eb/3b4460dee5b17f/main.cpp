/*
 * CSE 251 Project 1
 * By: <NAME>
 *
 * Complete the flowing table;
 *
 * a    	b		n		estimate
 * -1		1		1883	1.178979838
 * 0		10		2028	0.489888070
 * -1000	1000	18863	0.999796418
 * 10		15		1515	0.016860599
 * 0.1		0.2		138		0.096211811
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/**
 * imply Equation (2)
 * 		f(x) = sin(pi*x)/(pi*x)
 */
double function(double x) {
	if (x == 0) // assume f(0) = 1
		return 1;

	return sin(M_PI * x) / (M_PI * x);
}

int main() {
	double a, b;
	printf("Enter a value for a: ");
	scanf("%lf", &a);
	printf("Enter a value for b: ");
	scanf("%lf", &b);
	printf("Integral evaluation\n");

	double diffAB = b - a; // difference between a & b

	int i;
	int n = 10; // always start with 10

	double oldIntegral = 0;
	double newIntegral = 1; // must let newIntegral - oldIntegral > 1e-10

	while (n <= 100000) { // if can cut into n pieces
		double delta = diffAB / n; // Equation (4)

		oldIntegral = newIntegral; // store old integral

		newIntegral = 0; // assign zero and recalculate the value
		for (i = 1; i <= n; ++i) { // Equation (7)
			newIntegral += function(a + i * delta - 0.5 * delta) * delta;
		}
		printf("%d: %.9lf", n, newIntegral);

		double error = fabs(oldIntegral - newIntegral); // convert error to absolute value
		if (n != 10)
			printf(" %.6e", error); // output the error
		printf("\n");

		if (error < 1e-10) // break if error is small enough
			break;
		++n;
	}
	printf("The integral result is: %lf\n", newIntegral); // final answer

	return 0;
}
