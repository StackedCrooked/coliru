#include <math.h>
#include <stdio.h>

int main()
{
    double jdn = 10.11;
    double jdn_frac = jdn - floor(jdn);
    
    printf("jdn = %g, jdn_frac = %g\n", jdn, jdn_frac);

    int h = (int)(jdn_frac * 24.0);
    int m = (int)((jdn_frac * 24.0 - h) * 60.0);
    int s = (int)(((jdn_frac * 24.0 - h) * 60.0 - m) * 60.0);
    
    printf("%02d:%02d:%02d\n", h, m, s);

    return 0;
}
