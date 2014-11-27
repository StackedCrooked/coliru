#include <iostream>
using namespace std;
bool odd(int);

bool even( int n ) {
  if ( n==0 ) return true;
  else return odd( n-1 );
}
bool odd( int n ) {
  if ( n==0 ) return false;
  else return even( n-1 );
}

int main() {
  for ( int n=1; n<=20; n++ )
    cout << n << " is " << (even(n)? "even":"odd") << endl;
}