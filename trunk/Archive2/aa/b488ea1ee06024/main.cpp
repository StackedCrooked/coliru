#include <queue>
#include <stack>
#include <mutex>
#include <thread>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <condition_variable>

template <class F>
class thread_pool
{
    static_assert(std::is_function<F>::value, "F must have function type");
public:
    thread_pool();
    ~thread_pool();
    template <class Task>
    void push(Task&&);
private:
    std::unordered_map<std::thread::id, std::thread> workers;
    std::queue<std::thread> waiters;
    std::stack<std::function<F>> tasks;
    static std::size_t max;
private:
    std::condition_variable m_cond;
    std::mutex m;
private:
    void wait_for_tasks();
};

template <class F>
std::size_t thread_pool<F>::max(10);

template <class F>
thread_pool<F>::thread_pool()
{
    std::lock_guard<std::mutex> lock(m);
    for (std::size_t i = 0; i < max; ++i)
        waiters.emplace(&thread_pool<F>::wait_for_tasks, this);
}

template <class F>
void thread_pool<F>::wait_for_tasks()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m);
        m_cond.wait(lock, [this] { return !tasks.empty(); });
        
        auto f = tasks.top();
        tasks.pop();
        auto& th = workers[std::this_thread::get_id()];
    
        if (th.get_id() == std::thread::id())
            th = std::thread(f);
    }
}

template <class F>
template <class Task>
void thread_pool<F>::push(Task&& t)
{
    {
        std::lock_guard<std::mutex> lock(m);
        tasks.emplace(std::forward<Task>(t));
    }
    m_cond.notify_all();
}

template <class F>
thread_pool<F>::~thread_pool()
{
    std::for_each(workers.begin(), workers.end(), [] (std::pair<std::thread::id const, std::thread>& p)
    {
        if (p.second.joinable())
            p.second.detach();
    });
    
    while (!waiters.empty())
    {
        auto& t = waiters.front();
        waiters.pop();
        if (t.joinable())
            t.detach();
    }
}

int main()
{
    thread_pool<void ()> pool;
}