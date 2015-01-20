#include <iostream>
#include <string>
#include <vector>
#include<iomanip>


using namespace std;

int main ( )
{

double sPay; // salary payrate
double rate; // percent rate based on proformance  
char pRating; // proformance rating
double pPercent; // pay percent to be add to salary

    cout << "Enter the starting salary per hour: "; // prompts user to input their salary per hour
	cin >> sPay; // reads in user's input for salary per hour  

	cout << "\n"; // just a new blank line

	cout << "Enter the performance rating 'A', 'B', or 'C': "; // prompts user to input a performance rating
	cin >> pRating; // reads in user's input for performance rating
	
	cout << "\n"; // just a new blank line

	if(pRating == 'A'|| pRating == 'a') // performs the block of code if the user inputs 'A' or 'a' as a choice
		{
		rate = .05; // set rate of .05
		
		pPercent = rate * sPay; // calculates the pay percent to be add to salary
		sPay = sPay + pPercent; // calculates the new salary payrate
		
		cout << "Your new payrate is $" << setprecision(2) << fixed << showpoint << sPay << " per hour "<< endl; // outputs the new salary payrate 
		}
	else if (pRating == 'B'|| pRating == 'b') // performs the block of code if the user inputs 'B' or 'b' as a choice
		{
		rate = .03; // set rate of .03
		
		pPercent = rate * sPay; // calculates the pay percent to be add to salary
		sPay = sPay + pPercent; // calculates the new salary payrate
		
		cout << "Your new payrate is $" << setprecision(2) << fixed << showpoint << sPay << " per hour "<< endl; // outputs the new salary payrate
		}
	else if (pRating == 'C'|| pRating == 'c') // performs the block of code if the user inputs 'C' or 'c' as a choice
		{
		rate = .01; // set rate of .01
		
		pPercent = rate * sPay; // calculates the pay percent to be add to salary
		sPay = sPay + pPercent; // calculates the new salary payrate
		
		cout << "Your new payrate is $" << setprecision(2) << fixed << showpoint << sPay << " per hour "<< endl; // outputs the new salary payrate
		}
	else  // performs the block of code if the user inputs anything other than the correct choices
		{
		rate = .005; // set rate of .005
	
		pPercent = rate * sPay; // calculates the pay percent to be add to salary
		sPay = sPay + pPercent; // calculates the new salary payrate

		cout << "Your new payrate is $" << setprecision(2) << fixed << showpoint << sPay << " per hour "<< endl; // outputs the new salary payrate
		}

cout << "Goodbye!"; // end of program statement
		
return 0;
}
