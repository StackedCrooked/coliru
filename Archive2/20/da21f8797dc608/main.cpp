#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int fib(int x)
{
    if (x <= 1)
	{
		return x;
	}
	else
	{
		return fib(x - 1) + fib(x - 2);
	}
}

int main()
{
	int stop = -1;

	while (stop != 1)
	{
		cout << "How many numbers of the fibonacci sequence do you want? ";
		cout << "Enter number : ";
		int number;
		
		cin >> number;
		
		cout << endl;

		int i = 0;
		
		while (i <= number)
		{
			cout << fib(i) << " ";
			i++;
		}

		cout << endl << "Do you want to continue? (Y/N) ";
		cout << "Enter option : ";

		char option;
		cin >> option;

		if (option == 'N')
		{
			stop = 1;
		}
	}
	return 0;
}