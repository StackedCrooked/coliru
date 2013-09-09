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
    Item item{3};
    boost::circular_buffer<Item> buf;
    buf.set_capacity(2);
    for (int i = 0; i != 4; ++i)
    {
        std::cout << i << ": ";
        buf.push_back(i);
    }
}
