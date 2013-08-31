#include <iostream>

template <typename T>
void foo(T& y)
{
   y++;
}

int main()
{
   int x = 5;

   // Why won't this line work???/
   foo(x);

   std::cout << x;
}