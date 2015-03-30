#include <iostream>

using namespace std;

int main()
    {
    cout << "Aqui é um texto somente,não realiza operações matemáticas 3+4*2" << endl ;
    cout << 3+4*2 << endl ;
    cout << (3+4)*2 << endl ;
    cout << (256*256)+(1024*16) << endl ;
    cout << 2*5*5+3*5+7 << endl ;
    cout << (5+3*2) << endl ;
    cout << ((5+3)*2) << endl ;
    cout << (10.21/3.2+2.0)*(7.85*3.6+0.055) << endl ;
    cout.precision(5);
    cout << (10.21/3.2+2.0)*(7.85*3.6+0.055) << endl ;
    cout << 1.234567 << endl ;
    cout.precision(7);
    cout << 1.234567 << endl ;
    cout << 7/2 << endl ;
    cout << 7%2 << endl ;
    cout << 7.0/2 << endl ;
    cout << 7/2.0 << endl ;
    cout << 7.0/2.0 << endl ;
    return 0;
    }
