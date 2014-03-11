#include <iostream>
#include <initializer_list>

int main()
{
    for (auto&& e : { 1, 2, 3 })
            std::cout << e << "\n";    
}
