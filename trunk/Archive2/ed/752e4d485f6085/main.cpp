#include <stdio.h>
#include <math.h>

int main()
{
    int theta;

    for (theta = 0; theta <= 360; theta += 45)
    {
        double theta_r = 2.0 * M_PI * theta / 360.0;
        double x = cos(theta_r);
        double y = sin(theta_r);
        double degrees = atan2(x, y) * 360.0 / (2.0 * M_PI) + 180.0;
        printf("theta = %4d, x = %12g, y = %12g, degrees = %4g\n", theta, x, y, degrees);
    }
    return 0;
}