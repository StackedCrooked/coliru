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
        std::packaged_task<Item()> task([=]{
            return Item(get_component().get());
        });
        std::thread(std::move(task)).detach();
        return task.get_future();
    }
    
    std::future<Component> get_component();
};

int main()
{
}