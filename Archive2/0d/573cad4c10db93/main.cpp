#include <iostream>


struct Item
{
    Item()
    {
        std::cout << "Item" << std::endl;
    }
       
    ~Item()
    {
        std::cout << "~Item" << std::endl;
    }
       
};


thread_local Item item;


int main()
{
}
