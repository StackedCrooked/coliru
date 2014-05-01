#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct X{};
X y;
//template <class X>
/*void foo(X&)
{cout << "Inside Lval" << endl;}*/

//template <class X>
void foo(X&&)
{cout << "Inside Rval" << endl;}

X ret()
{ return y; }

int main()
{
  //int x = 10;
  X x;
  foo(x);
  foo(ret());
  //int y = ret();
  //foo(ret());
  //cout << y << endl;
}
