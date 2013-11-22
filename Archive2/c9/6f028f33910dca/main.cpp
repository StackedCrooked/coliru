#include <iostream>
#include <math.h>

int main()
{
    double currYVel = 16.002880016580544;
    double currXVel = 32.001440113776916;
    double xsqr = pow(currXVel,2.0);
    double ysqr = pow(currYVel,2.0);
    double sum = xsqr+ysqr;
    double root = sqrt(sum);
    double div = currYVel/root;
    double test = asin(div);
    
    std::cout << div << " " << test << std::endl;

}
