
#include <cstdlib>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    float f = -3.3f;
    cout << abs(f) << endl;
    cout << std::abs(f) << endl;
    cout << fabs(f) << endl;
    
	return 0;
}