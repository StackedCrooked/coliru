#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <float.h>

int main()
{
    double a = DBL_MIN;
    double ticksize = DBL_EPSILON;
    std::cout << a/ticksize << " " << (a+ticksize)/(ticksize) << std::endl;
}
