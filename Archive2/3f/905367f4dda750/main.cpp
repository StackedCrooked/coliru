#include <iostream>
#include <string>
 
char const* abc()
{
char const* s = "abc";
 
return s;
}
 
char const* bc()
{
char const* s = "bc";
 
return s;
}
 
int main()
{
using namespace std;
cout << abc() << endl;
cout << bc() << endl;
cout << (abc()+1 == bc()) << endl;
return 0;
}