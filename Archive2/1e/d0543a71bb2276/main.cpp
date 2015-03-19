#include <iostream>
#include <functional>
#include <type_traits>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

struct Item
{
    Item()
    {
        TRACE
    }
        

    // From Effective Modern C++ Item 27 "Constraining templates that take universal references"
    template<typename F,
             typename = typename std::enable_if<!std::is_base_of<Item, typename std::decay<F>::type>::value>::type> 
    Item(F&& f) : mFunction(std::forward<F>(f))
    {
        TRACE
    }
    
    
    Item(Item&&) { TRACE }
    
    Item& operator=(Item&&)
    {
        TRACE
        return *this;
    }
    
    Item(const Item&) { TRACE }
    
    Item& operator=(const Item&)
    {
        TRACE
        return *this;
    }
    
    ~Item() { TRACE }
    
    
    std::function<void()> mFunction;
};



int main()
{
    Item item([]{});
    Item item2(item);
    item = item2;
    item2 = std::move(item);
    Item([]{ return 42; }) = Item(Item(std::move(item2)) = std::move(item));
}
