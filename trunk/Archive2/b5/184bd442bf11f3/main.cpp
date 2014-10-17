#include <functional>
#include <mutex>
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <tbb/concurrent_queue.h>


static std::mutex fMutex;
    
void print_impl(std::lock_guard<std::mutex>&)
{
}
    
template<typename Head, typename ...Args>
void print_impl(std::lock_guard<std::mutex>& lock, const Head& head, const Args& ...args)
{
    std::cout << head << ' ';
    print_impl(lock, args...);
}
    
template<typename ...Args>
void print(const Args&... args)
{
    std::lock_guard<std::mutex> lock(fMutex);
    print_impl(lock, args...);
    std::cout << std::endl;
}

struct WorkerPool;


typedef std::function<void()> Task;


struct Thread
{
    template<typename F>
    Thread(F&& f) : mThread(std::forward<F>(f)) {}
    
    ~Thread() { mThread.join(); }
    
    Thread(Thread&&) = default;
    Thread& operator=(Thread&&) = default;
    
    Thread(const Thread&) = delete;
    Thread& operator=(Thread&) = delete;
    
    
    std::thread mThread;
};

struct Worker
{
    Worker(WorkerPool& inWorkerPool) : mWorkerPool(inWorkerPool), mThread([=]{
        auto thread_id = std::this_thread::get_id();
        print("Thread started:", thread_id);
        std::this_thread::yield(); // allow other threads to startup 
        try {
            worker_thread();
        } catch (...) {
            print("Exiting thread", thread_id);
        }
    })
    {}
    
    Worker(Worker&&) noexcept = default;
    Worker& operator=(Worker&&) noexcept = default;
    
    
    ~Worker()
    {
        mThread.join();
    }
    
    
    void add_local(Task task)
    {
        mLocalTasks.push_back(std::move(task));
    }
    
    void worker_thread();
    
    
    WorkerPool& mWorkerPool;
    std::vector<Task> mLocalTasks;
    std::thread mThread;
};


struct WorkerPool
{
    enum { num_workers = 6 };
    
    WorkerPool()
    {
        mWorkers.reserve(num_workers);
        while (mWorkers.size() != mWorkers.capacity())
        {
            mWorkers.emplace_back(*this);
        }
    }
    
    ~WorkerPool()
    {
        for (auto& worker : mWorkers)
        {
            mTaskQueue.push([]{ throw "stop"; });
        }
        sleep(1);
    }
    
    void push(Task&& task)
    {
        mTaskQueue.push(std::move(task));
    }
    
    void pop(Task& task)
    {
        mTaskQueue.pop(task);
    }
    
    std::vector<Worker> mWorkers;
    tbb::concurrent_bounded_queue<Task> mTaskQueue;
    
};
    

void Worker::worker_thread()
{
    Task task;
    for (;;)
    {
        if (!mLocalTasks.empty())
        {
            auto local_tasks = std::move(mLocalTasks);
            mLocalTasks.clear();
            
            for (auto& task : local_tasks)
            {
                task();
            }
        }
        
        mWorkerPool.pop(task);
        task();
        std::this_thread::yield();
    }
}


static WorkerPool& GetWorkerPool()
{
    static thread_local WorkerPool fWorkerPool;
    return fWorkerPool;
}


int main()
{
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    GetWorkerPool().push([]{ print(std::this_thread::get_id(), __LINE__ ); });
    sleep(1);
}


