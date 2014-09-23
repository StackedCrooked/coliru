#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

int main()
{

    int A, B, C, D, E, F;
	A = 0;
	B = 0;
	C = 0;
	D = 1;
	E = 0;
	F = 0;


	system("pause");
	system("cls");

	A = 0;
	do
	{
		A++;
		B = 0;
		do
		{
			B++;
			C = 0;
			do
			{ 
				cout << "doggy" << setw(5) << D++ << "\n";
				C++;
			} while (C < 5);
		} while (B < 5);
	} while (A < 5);



	cout << "\n\n\n\n\n\n\t\t\t";


	return 0;


}


