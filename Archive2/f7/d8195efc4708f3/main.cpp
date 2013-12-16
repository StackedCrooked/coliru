#include <iostream>

using namespace std;

void f()
{
  int a = 0;
  decltype(auto) b = a;
  b++;
  cout << a << b << endl;
}

void g()
{
  int a = 0;
  decltype(auto) b = (a);
  b++;
  cout << a << b << endl;
}

int main() {
  f();
  g();
  return 0;
}
