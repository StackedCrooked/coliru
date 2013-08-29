#include <cassert>
#include <iostream>
#include <vector>

struct Item
{    
    friend void operator delete(void *)
    {    
        std::cout << "NO!" << std::endl;
    }
};


int main()
{
    Item * item = new Item;
    delete item;
    delete item;
    delete item;
}