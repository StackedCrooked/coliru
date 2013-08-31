#include <iostream>
#include <memory>

struct Item
{
    Item() = default;
    
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;
    
    Item(Item&&) = default;
    Item& operator=(Item&&) = default;
};

Item a()
{
    Item item;
    return item;
}

Item b()
{
    static Item item2;
    return item2;
}

int main()
{
    a();
    b();
}