

#include <iostream>


#define TRACE() std::cout << __PRETTY_FUNCTION__ << std::endl


struct Item
{
    Item() { TRACE(); }
    
    ~Item() { TRACE(); }
    
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
    std::cout << "Without std::move: " << std::endl;
    func(make_item());
    
    std::cout << "\nWith std::move: " << std::endl;
    func(std::move(make_item()));

}
