#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<cstdlib>
#include <time.h>
#include <string>
using namespace std;

int main()
{
    int neatreset = 0;
beginning:
	int sides = 0;
	int rolls = 0;
	int rollsint = 1;
	int result = 0;
	int outputsum = 0;

	int currentroll = 2;
	string another = "";



	srand(time(0));

	if (neatreset == 0)
	{
		cout << "Number of Sides on Dice: \n";
		cin >> sides;
	}
	else if (neatreset == 1)
	{
		cout << "\n\nNumber of Sides on Dice: \n";
		cin >> sides;
	}


	cout << "\nNumber of Dice Rolled: \n";
	cin >> rolls;

	while (rolls > 0)
	{
		if (rollsint == 1)
		{
			result = rand() % sides + 1;
			cout << "\nRoll 1: " << result << "\n";
			rolls -= 1;
			rollsint -= 1;
			outputsum += result;
		}
		else
		{
			result = rand() % sides + 1;
			cout << "Roll " << currentroll << ": " << result << "\n";
			rolls -= 1;
			outputsum += result;
			currentroll += 1;
		}
	}

	cout << "\nSum: " << outputsum << "\n";
	cout << "\nAnother? (Y/N)\n";
	cin >> another;
	if (another == "y" || another == "Y"){
		neatreset = 1;
		goto beginning;
	}
	if (another == "n" || another == "N"){
		return 0;
	}


}