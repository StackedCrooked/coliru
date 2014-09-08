#include <iostream>
#include <type_traits>

using namespace std;

int main()
{
  float x, &r = x;
  [=]
  {
      cout << is_same<decltype((r)), float const&>::value;
   }();
}