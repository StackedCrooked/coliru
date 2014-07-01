/*
 * A Program that generates random numbers
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAX 5

int getrand( int min,int max )
{
    return( rand()%(max-min)+min );
}

int main()
{
    // array of integer
    const int GLOBE_PREFIX [ MAX ] =
    {
        917, 915, 817, 906, 905
    };

    const int SMART_PREFIX [ MAX ] =
    {
        908, 907, 908, 909, 912
    };

    srand( time(NULL) ); // seed the random number generator

    // generate ten random globe and smart number
    for( int i = 0; i < 10; ++i )
    {
        // must be 3 digits
        // beetween 100-999

        // get random number beetween 0 and 4
        int N = rand() % MAX;  // globe
        int NN = rand() % MAX; // smart

        cout << "Globe: " << "+63" << GLOBE_PREFIX[N]
             << " " << getrand(100, 999) << " " << getrand(1000, 9999) << '\n';
        cout << "Smart: " << "+63" << SMART_PREFIX[NN]
             << " " << getrand(100, 999) << " " << getrand(1000, 9999) << '\n';
        cout << "----------------------------------------\n";
    }
}
