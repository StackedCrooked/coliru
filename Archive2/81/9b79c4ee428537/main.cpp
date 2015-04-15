#include <iostream>
using namespace std;
struct S
{
   int a;
};
int main()
{
   S b;
   b={1};
   cout << b.a;
   b={2};
   cout << b.a;
   return 0;
}