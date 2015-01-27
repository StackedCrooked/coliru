#include <iostream>
#include <vector>
using namespace std;
double cube( double );
int main( )
{
using namespace std;
double R0 = 12.;
cout << "Cube of " << R0 << " is " << cube( R0 ) << endl;
return 0;
}
double cube( double x ) //definizione
{
return (x * x * x);
}
