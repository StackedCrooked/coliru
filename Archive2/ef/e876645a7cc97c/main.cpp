#include <iostream>

template<typename T>
void g(T t)
{
    t = 10;
    std::cout << t << '\n';
}

void f(const int i) { i = 10; std::cout << i << '\n'; }


int main()
{
   f(1);
   void(*pg)(const int) = g;
   pg(1);
}