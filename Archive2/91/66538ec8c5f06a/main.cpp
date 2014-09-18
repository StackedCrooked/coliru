
#include <iostream>
#include "math.h"

using namespace std;

int main()
{
    float deg_f = 90.0;
    float rad_f = deg_f / 360.0 * 2.0 * M_PI;
    
    double deg_d = 90.0;
    double rad_d = deg_d / 360.0 * 2.0 * M_PI;

    cout.precision(14);

    if( rad_f <= M_PI/2.0)
    {
        cout << rad_f << " less or equal " << M_PI / 2 << endl;
    }
    else
    {
        cout << rad_f << " larger " << M_PI / 2 << endl;
    }

    if( rad_d <= M_PI/2.0)
    {
        cout << rad_d << " less or equal " << M_PI / 2 << endl;
    }
    else
    {
        cout << rad_d << " larger " << M_PI / 2 << endl;
    }
    return 0;
}