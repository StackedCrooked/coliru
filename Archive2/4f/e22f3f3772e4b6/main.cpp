#include <iostream>
using namespace std;
 
int main()
{
 
enum A{a=9223372036854775808,b=~9223372036854775808 + 1};
cout << a << endl;
cout << sizeof(a) << endl;
cout << b << endl;
 
 
}