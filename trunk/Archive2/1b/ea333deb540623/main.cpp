/*
 * Cale Banfield c3132281 06/08/2014
 *
 * This program takes a lower limit and an upper limit temperature in celsius and then converts them to fahrenheit while displaying 
 * temperatures in between determined by a value entered by the user.
 *
 */


#include <iostream>
using namespace std;

int main(){
    
	double lowerLimit, upperLimit, 	/* Values input by the user for the lower and upper limit temperatures */ 	       	
	       celsius, fahrenheit;	/* Stores the value of both temperatures Celsius and Fahrenheit */
	int step;			/* This is the value in which the temperature will be incremented by when it is displayed */

	cout << "Enter the lower limit of temperature: ";
	cin >> lowerLimit;

	cout << "Enter the upper limit of temperature: ";
	cin >> upperLimit;

	cout << "Enter the step that the temperature will be incremented by: ";
	cin >> step;

	for (celsius = lowerLimit; celsius < upperLimit; celsius + step) { 	/* This loop starts from the lower limit and prints the celsius temperature and then    */
										/* the fahrenheit temperature, incremented by the step until it reaches the upper limit */
		
		fahrenheit = (9 / 5) * celsius + 32;
		
		cout << "Celsius: " << celsius << "   " << "Fahrenheit: " << fahrenheit << "\n";

	}
	
	return 0;
}