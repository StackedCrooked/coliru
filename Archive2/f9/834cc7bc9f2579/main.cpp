//       ____   __     __
//        /   /   \  /   \
//       /   /      /
//      /    \___/  \___/
//
// Date:
// Name:
// Project:
// Inputs:
// Outputs:
// Program Description:
//
//
//*************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std; //introduces namespace std

int main ( void )
{
    vector <int> celcius;
	cout << "Please enter any number of celcius values, enter an invalid\n"
		 << "temperature (< -273) to continue.\n";
	
 	while(true)
 	{
 		cout << "Enter a value: ";
 		int value;
 		cin >> value;
 		if (value < -273)
 			break;
 		else
 			celcius.push_back(value);
 	}
 	sort(celcius.begin(), celcius.end());
 	cout << "\n\nEntered values:\n";
 	for(int i=0; i<celcius.size(); i++)
 	{
 		cout << celcius[i] << endl;
 	}

 	cout << "\nSum: " << accumulate(celcius.begin(), celcius.end(), 0);
 	//get min
	int val = *min_element(celcius.begin(), celcius.end());
 	cout << "\nMaximum: " << val;

	//get max
	val = *max_element(celcius.begin(), celcius.end());
 	cout << "\nMinimum: " << val;
    return 0;
}
