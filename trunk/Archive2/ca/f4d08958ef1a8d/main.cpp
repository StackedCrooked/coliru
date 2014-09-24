
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int A = 0, B = 0, C = 0, D = 0;    // your 'real' data interest...
    
	do
	{
		A++;
        cout << "(A++) A is " << A << " B is " << B << " C is " << C << "\n";
		do
		{
			B++;
            cout << "(B++) A is " << A << " B is " << B << " C is " << C << "\n";
			do
			{ 
				cout << "doggy" << setw(5) << D++ << "\n";
				C++;
                cout << "(C++) A is " << A << " B is " << B << " C is " << C << "\n";
			} while (C < 5);
		} while (B < 5);
	} while (A < 5);

	return 0;
}
