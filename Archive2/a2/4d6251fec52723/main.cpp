#include <stdio.h>
#include <math.h>

#define MYABS(x) (x<0 ? -x : x)

double mycos(double x)
{
    double s = 1.0;
    double ti = s;
    double k = 1.0;
    x = -x*x;
    while (MYABS(ti) > 0)
    {
        ti = ti * x / ((k+1)*k);
        k = k + 2.0;
        s = s + ti;
    }
    return s;
}

int main()
{
    double x;
    if (scanf("%lf", &x) != 1)
        return 1;
    printf("mycos(%g) = %g\n", x, mycos(x));
    printf("cos(%g) = %g\n", x, cos(x));
    return 0;
}
