#include "stdio.h"
#include "math.h"

int main()
{
    double z = 21;
    double y = 0.04642;
    double x = -15.246;
    double s = -182.038;
    
    double res = log(pow(y, -sqrt(fabs(x))))*(x - y/2) + pow(sin(atan(z)), 2);

    printf("res = %f\n", res);
    if(fabs(res - s) < 0.001)
    {
        printf("Ok\n");
    }
    else
    {
        printf("Wrong\n");
    }
}
