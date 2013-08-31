#include <iostream>
#include <vector>


template<typename T>
struct Item
{
    T n;
    
    template<typename ...Args>
    Item(Args && ...args) : n(std::forward<Args>(args)...) {}
    
    Item(Item&&) = default;
    Item& operator=(Item&&) = default;
    
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;    
};


int main()
{
    std::vector< Item<int> > items;
    int n = 1;
    items.emplace_back(n);
}