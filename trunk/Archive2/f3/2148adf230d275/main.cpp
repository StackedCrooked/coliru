#include <iostream>
using namespace std;

bool bears( int n, bool trace = false ) {
  if (trace) cout<< " -> " << n;
  if ( n == 42 ) return true;
  else if ( n%2 == 0 ) return bears( n/2, trace );
  else if ( n%3 == 0 || n%4 == 0 ) return bears( ((n%100)/10) * (n%10), trace ); 
  else if ( n%5 == 0 ) return bears( 42, trace );
  else return false;
}

int main() {
  const int size = 10; 
  int test[] =  { 250, 111, 100, 84, 64, 53, 42, 41, 20, 17 };
  for ( int k=0; k<size; k++ )
    cout << " :: bears(" << test[k] << ") = " << (bears(test[k], true) ? "win" : "loss") << endl;
}
