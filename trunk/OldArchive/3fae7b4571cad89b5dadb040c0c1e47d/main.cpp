#include <deque>
#include <future>
#include <functional>


int main()
{
    std::deque<std::function<void()>> list;
 
    
    {
        std::packaged_task<int()> task([]() { return 1; });
        list.push_back(std::move(task));
    }
    
    {
        std::packaged_task<bool()> task([]() { return false; });
        list.push_back(std::move(task));
    }
    
}
