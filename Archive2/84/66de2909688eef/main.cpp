#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
  
/** GPS ticks per degree. */
#define NAV_GPS_TICKS_PER_DEGR  11930464
/** GPS ticks per minute. */
#define NAV_GPS_TICKS_PER_MIN     198841
/** GPS ticks per second. */
#define NAV_GPS_TICKS_PER_SEC       3314.0
  
#define MINUTES                       60
#define SECONDS                       60
  
double wgs84ToDegree(int32_t const wgs84Angle)
{
    int32_t wgs84, degr, min;
    double sec, degree;
    
    wgs84  = wgs84Angle;
    degr   = wgs84 / NAV_GPS_TICKS_PER_DEGR;
    wgs84 %= NAV_GPS_TICKS_PER_DEGR;
    min    = wgs84 / NAV_GPS_TICKS_PER_MIN;
    wgs84 %= NAV_GPS_TICKS_PER_MIN;
    sec    = wgs84 / NAV_GPS_TICKS_PER_SEC; // NOTE: cast not necessary, because NAV_GPS_TICKS_PER_SEC is already a double!

    degree = degr + (min + (sec / SECONDS)) / MINUTES;

    return   degree;
}
  
int32_t degreeToWgs84(double const degree)
{
    int32_t sign, degr, min, wgs84;
    double deg, sec;

    deg   = degree;
    sign  = (deg > 0) ? 1 : -1;
    deg   = abs(degree);

    degr  = (int32_t) deg;
    deg   = (deg - degr) * MINUTES;
    min   = (int32_t) deg;
    deg   = (deg - min) * SECONDS;
    sec   = deg;

    wgs84 = degr * NAV_GPS_TICKS_PER_DEGR
          + min * NAV_GPS_TICKS_PER_MIN
          + (int32_t) (sec * NAV_GPS_TICKS_PER_SEC);
    return  wgs84 * sign;
}
  
/*--------------------------------------------------*/
typedef struct _coords
{
    int32_t wgs1, wgs2;
    double deg1, deg2;
} coords_t;
  
  
int main(int const argc, char const * const * const argv)
{
    coords_t c;
    char *n;

    if (4 == argc)
    {
        printf("Input:\n");
        if (0 == strcmp("WGS84", argv[1]))
        {
            c.wgs1 = strtol(argv[2], &n, 10);
            c.wgs2 = strtol(argv[3], &n, 10);
            c.deg1 = wgs84ToDegree(c.wgs1);
            c.deg2 = wgs84ToDegree(c.wgs2);
            printf("\tWGS84: (%d, %d)\n", c.wgs1, c.wgs2);
            printf("Converted:\n");
            printf("\tDegree: (%.8f, %.8f)\n", c.deg1, c.deg2);
            printf("And back:\n");
            printf("\tWGS84: (%d, %d)\n", degreeToWgs84(c.deg1), degreeToWgs84(c.deg2));
        }
        else
        if (0 == strcmp("Degree", argv[1]))
        {
            c.deg1 = strtod(argv[2], &n);
            c.deg2 = strtod(argv[3], &n);
            c.wgs1 = degreeToWgs84(c.deg1);
            c.wgs2 = degreeToWgs84(c.deg2);
            printf("\tDegree: (%.8f, %.8f)\n", c.deg1, c.deg2);
            printf("Converted:\n");
            printf("\tWGS84: (%d, %d)\n", c.wgs1, c.wgs2);
            printf("And back:\n");
            printf("\tDegree: (%.8f, %.8f)\n", wgs84ToDegree(c.wgs1), wgs84ToDegree(c.wgs2));
        }
        else
        {
            printf("First argument must be either WGS84 or Degree\n");
            return 1;
        }
        return 0;
    }
    printf("Invalid number of parameters\n");
    return 1;
}