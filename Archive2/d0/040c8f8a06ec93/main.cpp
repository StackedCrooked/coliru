#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <float.h>

int main()
{
    double a = 0.001;
    double ticksize = DBL_EPSILON+DBL_EPSILON+DBL_EPSILON+DBL_EPSILON+DBL_EPSILON+DBL_EPSILON+DBL_EPSILON+DBL_EPSILON+DBL_EPSILON;
    std::cout << (a/ticksize) + (a+ticksize)/(ticksize) << " " << DBL_EPSILON <<std::endl;
}
