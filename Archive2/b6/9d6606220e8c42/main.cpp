#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
void mul ( long long f[2][2], long long m[2][2] );

void power (long long f[2][2], long long int n );
int fibo (long long int n);
int main (void)
{
   for (int n = 1; n < 18; ++n)
        cout << n << '\t' << fibo(n) << endl;
    return 0;
} 

int fibo (long long int n)
{
 //   long long f[2][2] = {{1,1},{1,0}};
    long long f[2][2] = {{1,1},{1,0}};
    if ( n == 0 )
        return 0;
    else
        power(f,n);//n-1);
    return f[0][0];            
}


    void power (long long f[2][2], long long int n )
    {
        if ( n == 0 || n == 1)
            return;
        long long m[2][2] = {{1,1},{1,0}};
        if ( n % 2 == 0 )
        {
     //       mul(f,f);
            power(f,n/2);
            mul(f,f);
        }
        else
        {
            power(f,(n-1)/2);
            mul(f,f);
            mul(f,m);
    //        power(f,(n-1)/2);
        }
    }

void mul ( long long f[2][2], long long m[2][2] )  
{ 
    long long x = f[0][0]*m[0][0] + f[0][1]*m[1][0];
    long long y = f[0][0]*m[0][1] + f[0][1]*m[1][1];
    long long z = f[1][0]*m[0][0] + f[1][1]*m[1][0];
    long long w = f[1][0]*m[0][1] + f[1][1]*m[1][1];
    f[0][0] = x;
    f[0][1] = y;
    f[1][0] = z;
    f[1][1] = w;
}