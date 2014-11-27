#include <iostream>
using namespace std;
    
void PrintChar( int n, char c ) { for ( int k=0; k<n; k++) cout << c; }

void PrintTriangle( int ns, int nb ) {
    if ( ns < 1 ) return;
    PrintTriangle( ns-2, nb+1 );
    PrintChar( nb, ' ' ); PrintChar( ns, '*' ); PrintChar( nb, ' ' ); cout << endl;
}
void PrintTriangle( int n ) { cout<< n << ":" <<endl; PrintTriangle( 2*n-1, 0 ); }

int main() { PrintTriangle(3); PrintTriangle(7); PrintTriangle(12); }