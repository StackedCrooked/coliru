#include <future>
#include <thread>

template< class Function, class... Args>
std::future<typename std::result_of<Function(Args...)>::type> async( Function&& f, Args&&... args ) 
{
    std::packged_task<F(Args...)> task(std::forward<F>(f), std::forward<Args>(args)...);
    auto ret = task.get_future();
    std::thread t(std::move(task));
    t.detach();
    return ret;   
}

int main()
{
    async([]{});
}