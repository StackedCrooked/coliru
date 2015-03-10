#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <future>
#include <array>
#include <chrono>
#include <mutex>


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

    enum { capacity = 100000 };

    CircularPool() : mStorage() { }

    char* allocate(std::size_t n)
    {
        n = align(n);
        std::cout << "allocate " << n << '\n';
        auto offset = ((mOffset += n) - n) % mStorage.size();
        return mStorage.data() + offset;
    }

    void deallocate(char*, std::size_t n)
    {
        n = align(n);
        std::cout << "deallocate " << n << '\n';
    }

    static std::size_t align(std::size_t n)
    {
        auto r = n % sizeof(long double);
        return n + bool(r) * r;
    }

    std::array<char, capacity> mStorage;
    std::atomic<std::uint64_t> mOffset{0};
};


template<typename F, typename Alloc>
struct Task
{
    explicit Task(F f, Alloc alloc) : f(f), alloc(alloc) {}

    void operator()() const
    { f(); }

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



struct Dispatcher
{
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
    Dispatcher dispatcher;

    std::thread t([&]
    {
        boost::asio::io_service::work work(dispatcher.ios);
        dispatcher.ios.run();
    });

    std::thread u([&]
    {
        for (int i = 0; i != 10; ++i)
        {
            dispatcher.post([i]{ std::cout << i << std::endl; });
        }

        dispatcher.post([&]{ dispatcher.ios.stop(); });
    });

    t.join();
    u.join();
    std::cout << "Done." << std::endl;
}
