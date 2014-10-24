#include <iostream>
#include <initializer_list>

void print_all(std::initializer_list<int> xs)
{
    for (auto const& x : xs) { std::cout << x << " "; } 
}

int main()
{
    print_all({4, 8, 15, 16, 23, 42});
}
