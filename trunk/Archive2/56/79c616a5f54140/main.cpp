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


Item make_item() { return {}; }


void func(Item item) { }


int main()
{
    std::cout << "\nimplicit: " << std::endl;
    func(Item());
    
    std::cout << "\nwith std::move: " << std::endl;
    func(std::move(Item()));
    
    // => Don't help the compiler!
    // (See also http://channel9.msdn.com/Events/GoingNative/2013/Don-t-Help-the-Compiler)
}

