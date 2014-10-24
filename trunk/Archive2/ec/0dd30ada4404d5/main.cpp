#include <iostream>

template<typename... Ts>
void print_all(Ts const&... ts)
{
    auto swallow = {(std::cout << x << " ")...};
}

int main()
{
    print_all(1, 3.14, 'c', "Hello");
    
    std::cout << std::endl;
    
    print_all(1, 'c');
}