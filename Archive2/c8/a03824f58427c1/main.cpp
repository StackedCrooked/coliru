#include <iostream>


#define TRACE() std::cout << "  " << __PRETTY_FUNCTION__ << std::endl


struct Item
{
    Item() { TRACE(); }
    ~Item() { TRACE(); }

    Item(const Item&) { TRACE(); }
    Item& operator=(const Item&) { TRACE();  return *this; }

    Item(Item&&) { TRACE(); }
    Item& operator=(Item&&) { TRACE(); return *this; }
};


void func(Item item) { }


int main()
{
    std::cout << "implicit: " << std::endl;
    func(Item());
    
    std::cout << "\nwith std::move: " << std::endl;
    func(std::move(Item()));
}
