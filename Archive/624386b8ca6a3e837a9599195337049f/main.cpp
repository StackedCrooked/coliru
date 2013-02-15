#include <mutex>
#include <vector>
#include <functional>

struct dispatcher {
    using queue_type = std::vector<std::function<void()>>;
    using guard_type = std::lock_guard<std::mutex>;
    queue_type work;
    std::mutex mutex;
    
    template<typename Functor>
    void push(Functor&& functor)
    {
        guard_type guard(mutex);
        work.emplace_back(std::forward<Functor>(functor));
    }
    
    void operator()()
    {
        queue_type to_process;
        {
            guard_type guard(mutex);
            to_process = std::move(work);
        }
        
        for(auto&& task: to_process) {
            task();
        }
    }
};

int main()
{
}