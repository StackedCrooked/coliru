#include <iostream>
using namespace std;

int main() {
    for( int i = 0; i < 1000; i++ ) {
        cout
            << i    // print the iteration number
            << "\t" // print a tab
            << i%10 // print the remainder of the number divided by 10
            << endl;// new line!
    }
}