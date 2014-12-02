#include <iostream>
#include <string>
using namespace std;

int main() {
    string x = "Herro!";
    x = "FAK YU, NO HERRO!";
    cout << x << endl;

    ///////////////////////////////////
    
    string y;
    if( true ) {
        y = "This happens when true";
    } else {
        y = "This happens when false";
    }
    
    cout << y << endl;

    //////////////////////////////////
    
    for( int i = 0; i < 33; i++ ) {
        cout << i << " ";
    }
    cout << endl; // finish off with an endline! :3
    
    
    //////////////////////////////////
    int j = 10;
    while( j > 0 ) {
        cout << j << endl;
        j = j - 1;
    }
    
    cout << "return!" << endl;
    return 0;
}