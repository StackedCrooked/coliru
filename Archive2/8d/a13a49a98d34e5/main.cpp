
#include <iostream>
#include "math.h"

using namespace std;

int main()
{
    double deg = 90.0;
    double rad = deg / 360.0 * 2.0 * M_PI;

    if( rad <= M_PI/2.0)
    {
        cout << rad << " less or equal" << M_PI / 2;
    }
    else
    {
        cout << rad << " larger" << M_PI / 2;
    }
    return 0;
}