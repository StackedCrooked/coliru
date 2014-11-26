#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double PIs( int n ) {                  // plain recursive
  if ( n == 1 ) return 3.0;
  else return PIs( n-1 ) + (n%2==0 ? 4.0 : -4.0) / (double)((2*n-2) * (2*n-1) * 2*n);
}

double PIa( int n, double s=3.0 ) {    // accumulator recursive
  if ( n == 1 ) return s;
  else return PIa( n-1, s + (n%2==0 ? 4.0 : -4.0) / (double)((2*n-2) * (2*n-1) * 2*n));  
}

double PId( int n ) {                  // dynamic programming
  static double s = 3.0;
  if ( n == 1 ) return s;
  else return s += (n%2==0 ? 4.0 : -4.0) / (double)((2*n-2) * (2*n-1) * 2*n); 
}

int main() {
  for ( int n=1; n<=50; n++ )
    cout << setprecision(30) 
         << "  M_PI = \t" << M_PI
         << "\n    PI(" << n << ")=\t" << PIa(n) << "\n\n";
}