#include <iostream>

void print_all()
{
}

template<typename T, typename... Ts>
void print_all(T const& x, Ts const&... ts)
{
    std::cout << x << " ";
    print_all(ts...);
}

int main()
{
    print_all(1, 3.14, 'c', "Hello");
    print_all(1, 'c');
}