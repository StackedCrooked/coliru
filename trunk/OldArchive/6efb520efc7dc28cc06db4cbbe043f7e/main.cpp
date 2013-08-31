#include <iostream>
#include <memory>

std::unique_ptr<int> get_int()
{
    std::unique_ptr<int> n(new int(2));
    std::cout << *n << std::endl;
    return n;
}


int main()
{
    std::cout << *get_int() << std::endl;
}