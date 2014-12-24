#include <iostream>
using namespace std;

int main () {
    for( unsigned int i = 15; i > 0; i-- ) {
        for( unsigned int j = i; j > 0; j-- )
            cout << " ";
        
        for( unsigned int j = 15-i; j > 0; j-- )
            cout << "**";

        cout << endl;
    }
    
    cout << "Merry xmas!~" << endl;
}