#include <utility>


struct Item
{
    Item() = default;    
    Item(Item&&) = default;
    Item& operator=(Item&&) = default;
    
    // require user to be explicit when copying
    Item copy() { return *this; }
    
private:
    // prevent accidental copy
    Item(const Item&) = default;
};


int main()
{
    Item a;
    Item b = a.copy();
    a = std::move(b);
}
