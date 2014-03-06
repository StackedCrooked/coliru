#include <iostream>
#include <initializer_list>

int main()
{
    int x = 1, y = 2, z = 3;
    
    for (auto&& e : { &x, &y, &z })
            std::cout << *e << "\n";    
}
