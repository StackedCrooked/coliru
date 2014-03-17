/*
 * SimpleCalc.cpp
 *
 *                  Name: Muhammad Shafiq Bin Hamid
 *      	      ID  : 169443
 *   Problem Statement: How to write simple calculation of integer program.
 *           Solution : Using basic mathematics formula which are addition,
 *                      Subtraction, multiplication and division.
 *        Project Name: SimpleCalc
 *          Created on: 05/03/2014 (Version 1.0)
 */

#include<iostream>
using namespace std;

int main()
{
	double first, second;
	char option;

	do
	{
		cout << "Enter first number : ";
		cin >> first;
		cout << "Enter second number: ";
		cin >> second;
		cout << "Choose operation:"<< endl;
		cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division" << endl;
		cout << "Enter option: ";
		cin >> option;

		switch(option)
		{
		case '1':
			cout << "Result of addition is " << first + second << endl;
			break;
		case '2':
			cout << "Result of subtraction is " << first - second << endl;
			break;
		case '3':
			cout << "Result of multiplication is " << first * second << endl;
			break;
		case '4':
			cout << "Result of division is " << first / second << endl;
			break;
		default:
			cout << "Invalid option! Try again" << endl;
		}
		cout << "Do you want to continue? Enter N/n to terminate, any Y/y to continue" << endl;
		cin >> option;
	}while(option != 'N' && option != 'n');

	return 0;
}

