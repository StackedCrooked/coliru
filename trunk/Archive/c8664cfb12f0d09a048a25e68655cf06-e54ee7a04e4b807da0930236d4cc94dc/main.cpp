#include <iostream>

struct Item
{
    // no state
    void foo() { std::cout << "Item::foo" << std::endl; }
};


int main()
{
    static_cast<Item*>(nullptr)->foo(); // ub?
}