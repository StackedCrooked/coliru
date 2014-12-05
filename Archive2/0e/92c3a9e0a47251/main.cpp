#include<iostream>
using namespace std;
int main( )
{
int a, b, c, max;
cout << "Enter a, b and c: ";
cin >> a >> b >> c;
max = a;
if (b>max)
    max = b;
if (c>max)
    max = c;
cout << "Max is " << max << "\n";
return 0;}
