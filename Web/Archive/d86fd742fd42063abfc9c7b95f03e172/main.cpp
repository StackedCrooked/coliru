#include <iostream>
#include <vector>


// Note:
// - target compiler is GCC 4.5.4 which does not support the `= default` syntax.
    
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
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;
    T n;
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

