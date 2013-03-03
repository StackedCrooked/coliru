#include <iostream>
using namespace std;

int main()
{
    //Variables
	int day,			//Number of days passed
		bugCollect;		//Bugs collected, recorded for every day
	int bugTotal = 0;	//Total bugs collected for program's span
		
	const int TIMESPAN = 7; //The number of days the program records for
	
	//Program
	cout << "This program will count the number of bugs you collected over " << TIMESPAN << " days.\n";
	
	for (day = 1; day <= TIMESPAN; day++)
	{
		cout << "Number of bugs collected on Day " << day << ": ";
		cin >> bugCollect;
		cout << endl;
	
		bugTotal += bugCollect;
	}
	
	cout << "You collected " << bugTotal << " bugs.";
	
	return 0;
}