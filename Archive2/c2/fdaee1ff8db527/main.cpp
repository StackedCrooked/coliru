#include <iostream>
#include <initializer_list>

template<typename T>
void print_all(std::initializer_list<T> xs)
{
    for (auto const& x : xs) { std::cout << x << " "; } 
}

int main()
{
    print_all({4, 8, 15, 16, 23, 42});
    print_all({"Hello", "World"});
}
