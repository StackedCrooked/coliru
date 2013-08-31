#include <iostream>
#include <string>

using namespace std;

int main()
{
    const string addition = "addition";
    const string substraction = "subtraction";
	const string multiplication = "multiplication";
	const string division = "division";
	string userinput;
	double variable1;
	double variable2;
	double answer;
	cout << "Please enter whether you would like to do addition, subtraction, multiplication, or division:" << endl;
	cin >> userinput;
	if (userinput == "addition")
	{
		cout << "Please enter the first number you want to add:" << endl;
		cin >> variable1;
		cout << "Please enter the second number you would like to add:" << endl;
		cin >> variable2;
		answer = variable1 + variable2;
		cout << "The sum of " << variable1 << " and " << variable2 << " is: " << answer << endl;
	}
	else if (userinput == "subtraction")
	{
		cout << "Please enter the first number you want to subtract:" << endl;
		cin >> variable1;
		cout << "Please enter the second number you would like to subtract:" << endl;
		cin >> variable2;
		answer = variable1 - variable2;
		cout << "The difference of " << variable1 << " and " << variable2 << " is: " << answer << endl;
	}
	else if (userinput == "multiplication")
	{
		cout << "Please enter the first number you want to multiply:" << endl;
		cin >> variable1;
		cout << "Please enter the second number you would like to multiply:" << endl;
		cin >> variable2;
		answer = variable1 * variable2;
		cout << "The product of " << variable1 << " and " << variable2 << " is: " << answer << endl;
	}
	else if (userinput == "division")
	{
		cout << "Please enter the first number you want to divide:" << endl;
		cin >> variable1;
		cout << "Please enter the second number you would like to divide:" << endl;
		cin >> variable2;
		answer = variable1 / variable2;
		cout << "The quotient of " << variable1 << " and " << variable2 << " is: " << answer << endl;
	}
	else 
	{
		cout << "FOLLOW MY GOD DAMN DIRECTIONS!!!!!!" << endl;
	}
	return 0;
}