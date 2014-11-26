#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double PIs( int n ) {                  // plain recursive
  if ( n < 0 ) return 0.0;
  else return PIs( n-1 ) + (4.0/(8*n+1) - 2.0/(8*n+4) - 1.0/(8*n+5) - 1.0/(8*n+6)) / pow(16,n);
}

double PIa( int n, double s=0.0 ) {    // accumulator recursive
  if ( n < 0 ) return s;
  else return PIa( n-1, s + (4.0/(8*n+1) - 2.0/(8*n+4) - 1.0/(8*n+5) - 1.0/(8*n+6)) / pow(16,n));  
}

double PId( int n ) {                  // dynamic programming
  static double s = 0.0;
  return s += (4.0/(8*n+1) - 2.0/(8*n+4) - 1.0/(8*n+5) - 1.0/(8*n+6)) / pow(16,n); 
}

int main() {
  for ( int n=0; n<=50; n++ )
    cout << setprecision(60) 
         << "  M_PI = \t" << M_PI
         << "\n    PIs(" << n << ")=\t" << PIs(n)
         << "\n    PIa(" << n << ")=\t" << PIa(n)
         << "\n    PId(" << n << ")=\t" << PId(n) << "\n\n";
}