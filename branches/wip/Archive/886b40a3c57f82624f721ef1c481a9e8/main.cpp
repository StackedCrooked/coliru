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

void b(Item item)
{   
    std::cout << &item << std::endl;    
}

int main()
{
    b(a());
    
    Item item = a();
    b(item);
}