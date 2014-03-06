#include <iostream>
#include <initializer_list>

struct B { virtual int fun() { return 0; } };
struct D1 : B { int fun() { return 1; } };
struct D2 : B { int fun() { return 2; } };

int main()
{
    D1 x;
    D2 y;
    
    B* px = &x;
    B* py = &y;
    
    for (auto& e : { px, py })
            std::cout << e->fun() << "\n";    
}
