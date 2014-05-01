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
        struct use_ptr : std::unique_ptr<Item> {
            using std::unique_ptr<Item>::unique_ptr;
            ~use_ptr() { release(); }
        };
        items.erase(use_ptr(&item));
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
