#include <future>
#include <thread>
#include <iostream>

template<class Function, class... Args>
std::future<typename std::result_of<Function(Args...)>::type> async( 
    Function&& f, 
    Args&&... args) 
{
    using R = typename std::result_of<Function(Args...)>::type;
    auto bound_task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
    auto task = std::packaged_task<R()>{std::move(bound_task)};
    auto ret = task.get_future();
    auto t = std::thread{std::move(task)};
    t.detach();
    return ret;   
}

int main()
{
    async([&] { std::cout << "Hello"; });
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
}