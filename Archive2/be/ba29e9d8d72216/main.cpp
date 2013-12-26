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




int main()
{
thread_local Item item;
}
