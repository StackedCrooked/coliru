#include <iostream>
#include <vector>


template<typename T>
struct Item
{    
    template<typename ...Args>
    Item(Args && ...args) : n(std::forward<Args>(args)...) {}
    
    Item(Item&& rhs) : n(std::move(rhs.n)) { }
    
    Item& operator=(Item&& rhs)
    {
        n = std::move(rhs.n);
        return *this;
    }
    
private:
    T n;
    Item(const Item&);
    Item& operator=(const Item&);    
};


int main()
{
    typedef Item<unsigned> Integer;
    std::vector<Integer> integers;
    for (unsigned i = 0; i < 10; ++i)
    {
        integers.emplace_back(i);
    }
}