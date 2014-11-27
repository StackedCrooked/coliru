#include <iostream>
#include <string>
using namespace std;

void stars( unsigned int n, unsigned int x = 0 ) {
  for (unsigned int k=0; k<x; k++) cout << "  ";
  for (unsigned int k=0; k<n; k++) cout << "* ";
  cout << endl;
}

void pattern( unsigned int n, unsigned int i ) {
  if ( n<0 || n & (n-1) ) { cout << "err: n must be a power of 2" << endl; return; }
  if ( n < 1 ) return;

  pattern( n/2, i );
  stars( n, i );
  pattern( n/2, i + n/2 );
}

int main() {
  for ( unsigned int n=2; n<20; n*=2 ) {
    cout << "pattern(" << n << "):" << endl;
    pattern(n, 0);
    cout << endl;
  }
}