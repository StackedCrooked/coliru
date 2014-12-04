

#include <iostream>


#define TRACE() std::cout << __PRETTY_FUNCTION__ << std::endl


struct Item
{
    Item() = default;
    Item(const Item&) { TRACE(); }
    Item& operator=(const Item&) { TRACE();  return *this; }
    
    Item(Item&&) { TRACE(); }
    Item& operator=(Item&&) { TRACE(); return *this; }
};


Item make_item() { return {}; }


void func(Item item)
{
}


int main()
{
    std::cout << "Without std::move: ";
    func(make_item());
    
    std::cout << "\nWith std::move: ";
    func(std::move(make_item()));

}
