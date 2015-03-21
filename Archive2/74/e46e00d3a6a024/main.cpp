#include <iostream>

using namespace std;

void printNum(int num)
{
    cout << num;

	if (num < 9)
	{
		printNum(num + 1);
	}
	cout << num;
}

int main()
{
	printNum(1);
	return 0;
}
