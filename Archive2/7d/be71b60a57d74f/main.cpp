#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main() {
    for( int x = 1; x <= 100; x++ ) {
       bool r3 = (x % 3) == 0;
       bool r5 = (x % 5) == 0;
       //cout << "debug " << x << "  " << r3 << "  " << r5 << "  " << endl;
       if( !r3 and !r5 ){
            cout << x << endl;
       } else if( r3 and !r5 ){
            cout << "Fizz" << endl;
       } else if( !r3 and r5 ){
            cout << "Buzz" << endl;
       } else{
            cout << "Fizz Buzz" << endl;
       }
    }
}