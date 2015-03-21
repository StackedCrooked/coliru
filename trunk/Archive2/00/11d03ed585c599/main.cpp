/*

I'm having trouble understanding how recursion is causing 'num' to count backward.

In main(), printNum() function receives num (with a value of '1'). As long as
num is less than 9, it will be incremented by 1. The first incrementation brings
num to 2. 2 is still less than 9, so we increment to 3, etc. until num reaches
the value of 9. We now exit the if statement and move to line 28, where num 
(with a value of 9) is printed again. 

I understand why the output of the program is 1,2,3,4,5,6,7,8,9,9 - 
but I do not understand why we then have 8,7,6,5,4,3,2,1. 

*/


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