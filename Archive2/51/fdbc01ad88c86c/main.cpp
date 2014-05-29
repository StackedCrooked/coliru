#include <iostream>

struct Item { };

void foo(const Item& item) { std::cout << "Item&" << std::endl; }
void foo(const Item&& item) { std::cout << "Item&&" << std::endl; }

Item bar()
{
    const Item item;
    return item;
}

int main()
{
    foo(bar());
}