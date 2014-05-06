#include <iostream>
#include <memory>
#include <set>


struct Collection;


struct Item
{    
    // enable default constructor
    Item() = default;
    
    // disable copy constructor and copy-assignment operator
    // (this also implicitly disables the move constructor and move-assignment operator)
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;
};


struct Collection
{   
    Item& add()
    {
        return **items.emplace(new Item).first;
    }
    
    void remove(Item& item)
    {
        std::unique_ptr<Item> p(&item);
        items.erase(p);
        p.release();
    }
    
    auto size() const
    {
        return items.size();
    }
    
private:
    std::set<std::unique_ptr<Item>> items;
};


int main()
{
    Collection collection;
    Item& item1 = collection.add();
    Item& item2 = collection.add();    
    collection.remove(item1);
}
