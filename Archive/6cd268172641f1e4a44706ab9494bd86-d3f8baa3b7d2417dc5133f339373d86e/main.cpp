#include <future>
#include <thread>
#include <type_traits>

template< class Function, class... Args>
std::future<typename std::result_of<Function(Args...)>::type> async( Function&& f, Args&&... args ) 
{
    typedef typename std::result_of<Function(Args...)>::type R;
    std::packaged_task<R(Args...)> task(std::forward<Function>(f), std::forward<Args>(args)...);
    auto ret = task.get_future();
    std::thread t(std::move(task));
    t.detach();
    return ret;   
}

int main()
{
    async([]{});
}