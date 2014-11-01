#include <utility>


struct Item
{
    Item() = default;
    
    Item(const Item&) = default;
    Item& operator=(const Item&) = default;
    
    Item& operator=(Item&&) = default;
    Item(Item&&) = default;
    
    // notifies user in case of unintended copy
    Item(const Item&&) = delete;
    Item& operator=(const Item&&) = delete;
};


int main()
{
    Item item;
    const Item item2 = std::move(item); // ok
    item = std::move(item2); // misleading
}
