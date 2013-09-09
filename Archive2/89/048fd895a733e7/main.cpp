#include <boost/circular_buffer.hpp>
#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


struct Item
{
    Item(int) { TRACE }
    Item(const Item&) { TRACE }
    Item(Item&&) { TRACE }
    
    Item& operator=(const Item&)
    {
        TRACE
        return *this;
    }
    
    Item& operator=(Item&&)
    {
        TRACE
        return *this;
    }
    
    ~Item() { TRACE }
};


int main()
{
    boost::circular_buffer<Item> buf;
    buf.set_capacity(1);
    
    std::cout << "Add first: " << std::endl;
    buf.push_back(Item{1});
    
    std::cout << "\nAdd second: " << std::endl;
    buf.push_back(Item{2});
}
