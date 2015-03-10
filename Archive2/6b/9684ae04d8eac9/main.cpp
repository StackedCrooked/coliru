#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <future>
#include <array>
#include <chrono>
#include <mutex>



// CircularPool is an "infinite" arena implemented as circular buffer.
// Deallocations *should* happen in same order as allocation.
// When buffer is full allocation starts again from the beginning.
// User must ensure that overflow won't happen (just like with a 
// regular arena).
struct CircularPool
{
    template<typename T>
    struct Allocator
    {
        Allocator(CircularPool& inCircularPool) : mCircularPool(&inCircularPool) { }

        void* allocate(std::size_t n)
        { return mCircularPool->allocate(sizeof(T) * n); }

        void deallocate(void* p, std::size_t n)
        { return mCircularPool->deallocate(static_cast<char*>(p), sizeof(T) * n); }

        CircularPool* mCircularPool;
    };

    explicit CircularPool(std::size_t capacity) : mStorage(capacity) { }

    char* allocate(std::size_t n)
    {
        n = align(n);
        //std::cout << "allocate " << n << '\n';
        
        // First alloc of n bytes will have offset n.
        // This prevents allocation at end-of-storage from overflowing the storage
        // because the wrap-around will make it point to the beginning.
        auto offset = (mOffset += n) % mStorage.size(); // TODO: (maybe) add check for detecting overuse
        return mStorage.data() + offset;
    }

    void deallocate(char*, std::size_t n)
    {
        // null-operation
        // n = align(n);
        //std::cout << "deallocate " << n << '\n';
    }

private:
    static std::size_t align(std::size_t n)
    {
        auto r = n % sizeof(long double);
        return n + bool(r) * r;
    }

    std::vector<char> mStorage;
    std::atomic<std::uint64_t> mOffset{0};
};


template<typename F, typename Alloc>
struct Task
{
    explicit Task(F f, Alloc alloc) : f(f), alloc(alloc) {}

    void operator()() const
    { f(); }

private:
    friend void* asio_handler_allocate(std::size_t n, Task<F, Alloc>* task)
    { return task->alloc.allocate(n); }

    friend void asio_handler_deallocate(void* p, std::size_t n, Task<F, Alloc>* task)
    { task->alloc.deallocate(static_cast<char*>(p), n); }

    F f;
    Alloc alloc;
};


template<typename F, typename Alloc>
Task<F, Alloc> MakeTask(F f, Alloc alloc)
{
    return Task<F, Alloc>(f, alloc);
}



struct TaskQueue
{
    TaskQueue() : pool(1000 * 1000) {}
    
    // post without return value
    template<typename F>
    void post(F&& f)
    {
        ios.post(MakeTask(f, CircularPool::Allocator<char>{pool}));
    }


    boost::asio::io_service ios;
    CircularPool pool;
};



int main()
{
    TaskQueue taskQueue;

    std::thread t([&]
    {
        boost::asio::io_service::work work(taskQueue.ios);
        taskQueue.ios.run();
    });

    std::thread u([&]
    {
        for (int i = 0; i != 100; ++i)
        {
            taskQueue.post([i]{ std::cout << i << std::endl; });
        }

        taskQueue.post([&]{ taskQueue.ios.stop(); });
    });

    t.join();
    u.join();
    std::cout << "Done." << std::endl;
}
