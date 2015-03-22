#include <iostream>
#include <iomanip>   // std::setprecision
using namespace std;

int main()
    {
    cout << "(10.21/3.2 + 2.0)*(7.85*3.6 + 0.055) = " << ((10.21/3.2 + 2.0)*(7.85*3.6 + 0.055)) << endl;
    cout << "(10.21/3.2 + 2.0)*(7.85*3.6 + 0.055) = " << setprecision(10) << ((10.21/3.2 + 2.0)*(7.85*3.6 + 0.055)) << endl;
    cout << " 5 / 2 = " << 5/2 << endl;
    cout << " 5.0/2 = " << 5.0/2 << endl;
    cout << " 5.0%2 = " << 5%2 << endl;
    return 0;
    }
