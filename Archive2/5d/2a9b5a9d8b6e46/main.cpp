#include <set>

struct Collection;

struct Item
{
    Item(Collection* collection);    
    ~Item();    
    Collection* parent;
};

struct Collection
{
    Collection() : destructing(false) {}
    
    ~Collection() {
        destructing = true;
        for (Item* item : items) {
            delete item;
        }
    }
    
    bool destructing;
    std::set<Item*> items;
};

Item::Item(Collection* collection) : parent(collection)
{
    collection->items.insert(this);
}

Item::~Item()
{
    if (!parent->destructing) {
        parent->items.erase(this);
    }
}

int main()
{
    // pointers are best
    Collection* collection = new Collection;
    
    Item* item1 = new Item(collection);
    Item* item2 = new Item(collection);
    
    delete item1;
    delete collection;
}
