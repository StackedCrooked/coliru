#include <future>
#include <thread>

struct Component { };

struct Item
{
    Item(Component component) : comp(component) {}    
    Component comp;
};

struct Factory
{
    std::future<Item> get_item()
    {
        // std::launch::deferred may be appropriate as well
        return std::async(std::launch::async, [=]{ return Item(get_component().get()); });
    }
    
    std::future<Component> get_component();
};

int main()
{
}