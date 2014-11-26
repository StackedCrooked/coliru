#include <iostream>
using namespace std;
    
int M ( int n ) {
  if ( n < 0 ) { cout<< "err: n must be positive" <<endl; return -1; }
  if ( n > 100 ) return n - 10;
  else return M (  M ( n + 11 ) );
}


int main() {
  int num=200, n=0;
  while(n++<num)
    cout<<" M("<< n <<")="<< M(n) <<endl;
}