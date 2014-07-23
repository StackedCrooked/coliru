#include <cmath>
#include <iostream>

double GetAngle(double s1,double s2,double s3)
{
    double r=acos((pow(s1,2)+pow(s2,2)-pow(s3,2))/(2*s1*s2));
    r=((180.0*r)/M_PI);
    return r;
}

int main()
{
    // acute angle
	std::cout << GetAngle(3, 4, 5) << std::endl;
	std::cout << GetAngle(3, 5, 4) << std::endl;
	std::cout << GetAngle(5, 4, 3) << std::endl;

	// obtuse angle
	std::cout << GetAngle(6, 6, 11.99) << std::endl;
}

