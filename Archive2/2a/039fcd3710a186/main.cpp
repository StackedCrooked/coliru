#include <iostream>
#include <cstdlib>
using namespace std;

int getRandomNumber (int min, int max);

int main()
{
    int seedNumber, z;

	cout << "enter the seed for the random number generator: ";
	cin >> seedNumber;
	cout << endl;
	srand(seedNumber);

	cout << "enter the minimum and maximum size of the random numbers: ";

	int min, max ; // **** added ****
	// cin >> min, max;
	cin >> min >> max ; // **** modified ****

	cout << endl;
	cout << endl;
	z = getRandomNumber(min, max);

	cout << "random number = " << z ;

    std::cout << "\n\n-----------------\n\n" ;

}

int getRandomNumber (int min, int max)
{
	int guess;
	guess = (rand() % (max - min + 1)) + min;
	return guess;
}
