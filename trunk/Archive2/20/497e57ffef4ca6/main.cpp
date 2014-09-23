
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int A = 0, B = 0, C = 0, D = 0;    // your 'real' data interest...
    
	do
	{
		A++;
		do
		{
			B++;
			do
			{ 
				cout << "doggy" << setw(5) << D++ << "\n";
				C++;
			} while (C < 5);
		} while (B < 5);
	} while (A < 5);

	return 0;
}
