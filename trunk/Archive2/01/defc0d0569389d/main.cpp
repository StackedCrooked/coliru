#include <iostream>
using namespace std;

int mian()
{
    int Minutes ;
	cout << "Enter the number of minutes: ";
	cin >> Minutes;
	cout << endl;
	cout << "This is ";
	cout << (Minutes/60);
	cout << ":";
	cout << (Minutes%60);
	cin.get();
	cin.get();
	return 0;
}

