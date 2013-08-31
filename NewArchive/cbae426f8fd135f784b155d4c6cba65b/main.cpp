#include <deque>
#include <future>
#include <functional>


int main()
{
    std::deque<std::function<void()>> list;
 
    
    {
        std::packaged_task<int()> task([]() { return 1; });
        std::function<void()> f(std::move(task));
        list.emplace_back(std::move(f));
    }
    
    {
        std::packaged_task<bool()> task([]() { return false; });
        std::function<void()> f(std::move(task));
        list.emplace_back(std::move(f));
    }
    
}
