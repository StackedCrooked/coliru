#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double Fx(double x);
double interp(double x, double step);

int main ()
{
    const double epsilon = 0.001 ;
    const double incr = 0.5 ;

    const double max_radians = 10.0 ;

    for( double x = 0  ; x < max_radians ; x += incr )
    {
        const double step = 0.001 ;

        while( Fx(x) > epsilon ) x = x + step; // *** epsilon

        if( x < max_radians )
        {
            cout << "\n x (iteration only) = " << setprecision(4) << x;
            cout << setprecision(6) << " with an error of " << Fx(x) - epsilon ;

            x = interp(x,step);
            cout << "\n x (with interpolation) = " << x;
            cout << " with an error of " << Fx(x) ;

            cout << "\n\n";
        }
    }
}

double Fx(double x)
{
  return abs( (sin(x)) - (exp(-0.4 * x)) ); // *** abs
}

double interp(double x, double step)
{
  double ratio;

  ratio = - Fx(x-step)/Fx(x);

  return (x - step + ratio * step /(1 + ratio));
}
