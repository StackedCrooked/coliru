#include <iostream>

void weird_print_all() { }

template<typename T, typename... Ts>
void weird_print_all(T const& x, Ts const&... ts)
{
    std::cout << x << " ";
    weird_print_all((ts + ts)...);
}

int main()
{
    weird_print_all(1, 3.14, 'c', std::string{"Hello"});
    
    std::cout << std::endl;
    
    weird_print_all(1, 'c');
}