#include <future>

struct Component { };

struct Item {
    Item(Component component) : comp(component) {}    
    Component comp;
};

struct Factory {
    std::future<Item> get_item()     {
        std::future<Component> component = get_component();        
        // how to get a std::future<Item> ?
    }
    
    std::future<Component> get_component();
};

int main()
{
}