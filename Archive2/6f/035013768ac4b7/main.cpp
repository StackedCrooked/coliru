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
        items.erase({ &item, { false } });
    }
    
private:
    struct maybe_delete
    {
        maybe_delete(bool b = true) : b(b) {}
        
        void operator()(Item* item) {
            if (b) delete item;
        }
        bool b;
    };
    std::set<std::unique_ptr<Item, maybe_delete>> items;
};


int main()
{
    Collection collection;
    Item& item1 = collection.add();
    Item& item2 = collection.add();
    
    collection.remove(item1);
}
