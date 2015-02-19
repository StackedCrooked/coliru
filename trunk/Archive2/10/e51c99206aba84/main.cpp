#include <iostream>
#include <random>
using namespace std;

const string target = "scrub";

int main() {
    mt19937 rng;

    unsigned long long cycle = 0;

    while( true ) {
        for( unsigned int i = 0; i < target.size(); i++ ) {
            cycle++;
            if( (char) (0x63+rng()%19) != target[i] )
                break;

            if( i == target.size()-1 ) {
                cout << cycle << endl;
                return 0;
            }
        }
    }
}