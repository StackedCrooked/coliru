#include <iostream>
#include <random>
using namespace std;
mt19937 rng(1424313798);
int main() {
    for( unsigned long long i = 0; i < 583617752; i++ ) rng();
    for( unsigned int i = 0; i < 7; i++ ) cout << (char)(97+(rng()%26)); cout << endl;
    return 0;
}