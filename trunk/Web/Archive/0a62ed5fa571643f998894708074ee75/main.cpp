#include <iostream>
#include <memory>

struct Item
{
    Item() = default;
    
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;
    
    //Item(Item&&) = default;
    //Item& operator=(Item&&) = default;
};

Item get()
{
    Item item;
    return item;
}


int main()
{
    Item item = get();
}