#include <iostream>

using namespace std;


int main()
{
    unsigned n = 0;
    
    
    n = ~(-1);
    cout << n << endl;
    
    unsigned n1010 = (1 << 1) | (1 << 3);
    unsigned n0101 = (1 << 0) | (1 << 2);
    
    n = n1010 & n0101;
    cout << n << endl;
    
    
    
    return 0;
}
