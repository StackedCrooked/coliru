#include <iostream>
#include <functional>

typedef std::function<void()> func1_t;
typedef std::function<void(int)> func2_t;

struct X
{
   X (func1_t f)
   { std::cout << "func1\n"; }

   X (func2_t f)
   { std::cout << "func2\n";}
};

int main ( )
{
   X x([](int){ std::cout << "Hello, world!\n"; });
}
