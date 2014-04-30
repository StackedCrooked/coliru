#include<iostream>
#include<array>

using namespace std;
const int Arsize = 101;
int main()
{
    array < long double, Arsize > tabarr;
    //tabarr[0]=1;
    // cout<<tabarr[0];
    tabarr[ 1 ] = tabarr[ 0 ] = 1;
    for( int i = 2; i < Arsize; i++ )
    {
        tabarr[ i ] = i * tabarr[ i - 1 ];
       
    }
    for( int i = 0; i < Arsize; i++ )
         cout << i << "! = " << tabarr[ i ] << endl;
   
   
     return 0;
   
}