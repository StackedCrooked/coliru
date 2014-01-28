#include <iostream>
#include <string>

using namespace std;

bool  any_capitals(const string &s)
{
    for (auto c : s)
	{
		if (isupper(c))
			return true;
	}
	return false;
}

void lowerise(string &s)
{
	for (auto &c : s)
	{
		c = tolower(c);
	}
}


int main()
{
	/////////////////////////////////////////////////
	// Exercise 6.17
	/////////////////////////////////////////////////

	// First part

	string myString = "HeLlO WoRlD!";

	bool capitals = any_capitals(myString);

	cout << "myString contains capitals: " << capitals << endl;

	// Second part

	cout << "----------------------------------" << endl;

	lowerise(myString);

	cout << myString << endl;



	int x = 0;
	cin >> x;

	return 0;
}