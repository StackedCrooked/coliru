
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int D = 0;    // your 'real' data interest...
    
    int A = 0;    // merely a loop variable
	do
	{
		A++;
		int B = 0;    // merely a loop variable
		do
		{
			B++;
			int C = 0;    // merely a loop variable
			do
			{ 
				cout << "doggy" << setw(5) << D++ << "\n";
				C++;
			} while (C < 5);
		} while (B < 5);
	} while (A < 5);

	return 0;
}
