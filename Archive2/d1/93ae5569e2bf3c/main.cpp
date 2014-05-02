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
        // hm, this should be simpler
        for (auto i = items.begin(), e = items.end(); i != e; ++i)
        {
            if (i->get() == &item)
            {
                items.erase(i);
                return;
            }
        }
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
