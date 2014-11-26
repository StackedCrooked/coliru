#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double FH1( int n ) {         // plain recursive
  if ( n == 1 ) return 1.0;
  else return FH1( n-1 ) + 1.0 / n;
}

double FH2( int n ) {         // plain recursive
  if ( n == 1 ) return 1.0;
  else return FH2( n-1 ) + (n%2==0 ? -1.0 : 1.0) / n;
}

int main() {
  for ( int n=1; n<=50; n++ )
    cout << setprecision(30) << "FH1(" << n << ")=\t" << FH1( n ) << endl
    	 << "log(" << n << ")=\t" << log( n ) << endl
		 << "FH2(" << n << ")=\t" << FH2( n ) << endl;
}