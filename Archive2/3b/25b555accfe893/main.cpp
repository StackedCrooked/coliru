#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main() {
    for( int x = 1; x <= 100; x++ ) {
        bool r3 = (x % 3) == 0;
        bool r5 = (x % 5) == 0;

        if( r3 )
            cout << "Fizz";

        if( r5 )
            cout << "Buzz";

        if( !r3 and !r5 )
            cout << x;

        cout << endl;
    }
}