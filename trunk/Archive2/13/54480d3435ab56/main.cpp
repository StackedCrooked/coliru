#include <memory>
#include <set>

struct Collection;

struct Item
{
};

struct Collection
{    
    Item& add()
    {
        return **items.emplace().first;
    }
    
    void remove(Item& item)
    {
        std::unique_ptr<Item> p(&item);
        items.erase(p);
        p.release();
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
