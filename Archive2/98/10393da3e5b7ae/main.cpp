#include<iostream>
using namespace std;
int main()
{
int j = 31234;
for( int i=1; i<=5; i++ )
{ 
 if( i%2 ) 
 { 
     if( i%4 ) 
       j += 4; 
 }
 else 
 j+=10; 
} 
cout << j << endl;
}


