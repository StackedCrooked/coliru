#include <iostream>
#include <string>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


struct Item
{
    template<typename T>
    T& operator,(T& )
    {
        TRACE
        return *this;
    }
    
    template<typename T>
    const T& operator,(const T& )
    {
        TRACE
        return *this;
    }
};


void test(Item&)
{
    TRACE
}


void test(Item& a, Item& b)
{
    TRACE
    std::cout << &a << ", " << &b;
}


int main()
{
    Item a, b;
    a,b;
    test(a, b);
}
