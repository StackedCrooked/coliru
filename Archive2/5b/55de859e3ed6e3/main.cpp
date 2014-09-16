#include <iostream>
#include <string>
#include <limits>
#include <stdint.h>
#include <math.h>

using namespace std;

void defineThis(double x) {
    double y = (double)((int64_t)x);
    if (y == trunc(x)) {
        cout << "casting " << x << " is well defined." << endl;
    } else {
        cout << "casting " << x << " is undefined!" << endl;
    }
}

int main()
{
    defineThis(3.5);
    defineThis(-3.5);
    defineThis(5);
    defineThis(std::numeric_limits<int64_t>::max());
    defineThis(std::numeric_limits<double>::max());
    defineThis(std::numeric_limits<double>::infinity());
    defineThis(std::numeric_limits<double>::signaling_NaN());
    defineThis(std::numeric_limits<double>::quiet_NaN());

    return 0;
}