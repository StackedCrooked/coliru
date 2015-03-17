#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>



class ThreadPool {
public:
    // Expand with copy and move semantics
    explicit ThreadPool(size_t = std::thread::hardware_concurrency());
    ~ThreadPool();
    
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;
    
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
 
// the constructor just launches some amount of workers
// grapje het is een pyramide xD
inline ThreadPool::ThreadPool(size_t threads)
    :   stop(false)
{
    for(size_t i = 0; i < threads; ++i) {
        workers.emplace_back(
            [this]
            {
                while (true) {
                    std::function<void()> task;

                    { // Scope the unique_lock
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this]
                            { 
                                return stop || !tasks.empty(); 
                            }
                        );
                        
                        if (stop && tasks.empty()) {
                            return;
                        }
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    task();
                }
            }
        );
    }
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using ret = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<ret()> >(
        std::bind(
            std::forward<F>(f), 
            std::forward<Args>(args)...
        )
    );
        
    std::future<ret> res = task->get_future();
   
    { // Scope the unique_lock
        std::unique_lock<std::mutex> lock(queue_mutex);

        if (stop) {
            throw std::runtime_error("Failed on enqueue");
        }

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline 
ThreadPool::~ThreadPool()
{
    { // Scope the unique_lock
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    
    condition.notify_all();
    for (auto& worker: workers) {
        worker.join();
    }
}











#include <iostream>


int main() {
    ThreadPool t;
    
    auto result = t.enqueue([](int answer) { 
        //std::this_thread::sleep_for(2);
        return answer;
    }, 42);
    
    std::cout << result.get() << std::endl;
}
