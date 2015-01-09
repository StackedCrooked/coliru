#include <iostream>


struct Item
{   
    Item& operator=(Item&) &
    {
        std::cout << "4";
        return *this;
    }
    
    Item& operator=(Item&) &&
    {
        std::cout << "3";
        return *this;
    }
    
    Item& operator=(Item&&) &
    {
        std::cout << "2";
        return *this;
    }
    
    Item& operator=(Item&&) &&
    {
        std::cout << "1";
        return *this;
    }
};


int main()
{
         Item() =      Item();
         Item() = *new Item();
    *new Item() =      Item();
    *new Item() = *new Item();
}
