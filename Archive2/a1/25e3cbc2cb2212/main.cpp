#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double HF( int n ) {                  // plain recursive
  if ( n < 0 ) return 0.0;
  else return HF( n-1 ) + (3.0 + 2.0 * n) / pow(2,n);
}

int main() {
  for ( int n=0; n<=60; n++ )
    cout << setprecision(30) << "HF(" << n << ")=\t" << HF(n) << endl;
}