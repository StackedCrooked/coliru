#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <future>
#include <array>
#include <chrono>
#include <mutex>



// CircularPool is an memory pool that uses a circular buffer
// as internal storage. I.e when the buffer is full then the
// next block will be allocated from the beginning.
//
// The user must specify a large enough capacity to ensure that
// overflow won't happen.
//
// Deallocations *should* happen in same order as allocation.
// However, this is not a hard requirement as long as it's certain
// that each allocated block will deallocated before its memory
// is reused.
//
// TODO: add debug checks to detect overflow
//
struct CircularPool
{
    template<typename T>
    struct Allocator
    {
        Allocator(CircularPool& inCircularPool) : mCircularPool(&inCircularPool) { }
        
        // TODO: implement allocator concept

        void* allocate(std::size_t n)
        { return mCircularPool->allocate(sizeof(T) * n); }

        void deallocate(void* p, std::size_t n)
        { return mCircularPool->deallocate(static_cast<char*>(p), sizeof(T) * n); }

        CircularPool* mCircularPool;
    };

    explicit CircularPool(std::size_t capacity) : mStorage(capacity) { }

    char* allocate(std::size_t n)
    {
        // TODO: debug checks to detect usage overflow
        
        // Note that the way the offset is calculated will cause the
        // first allocation to have an offset equal to its own size.
        // This seems weird, but it does prevent that allocation near
        // the end-of-storage would overflow the storage buffer.
        auto offset = (mOffset += align(n)) % mStorage.size();
        return mStorage.data() + offset;
    }

    void deallocate(char*, std::size_t)
    {
        // null-operation
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


//
// Example program
//


struct TaskQueue
{
    explicit TaskQueue(boost::asio::io_service& ios) : ios(ios), pool(1000 * 1000) {}
    
    template<typename F>
    void post(F f)
    {
        ios.post(MakeTask(f, CircularPool::Allocator<char>{pool}));
    }
    
private:
    template<typename F, typename Alloc>
    struct Task
    {
        explicit Task(F f, Alloc alloc) : f(f), alloc(alloc) {}
    
        void operator()() const
        { f(); }
    
    private:
        // asio allocation/deallocation hooks
        friend void* asio_handler_allocate(std::size_t n, Task<F, Alloc>* task)
        { return task->alloc.allocate(n); }
    
        friend void asio_handler_deallocate(void* p, std::size_t n, Task<F, Alloc>* task)
        { task->alloc.deallocate(static_cast<char*>(p), n); }
    
        F f;
        Alloc alloc;
    };
    
    template<typename F, typename Alloc>
    static Task<F, Alloc> MakeTask(F f, Alloc alloc)
    {
        return Task<F, Alloc>(f, alloc);
    }

    boost::asio::io_service& ios;
    CircularPool pool;
};



int main()
{
    boost::asio::io_service ios;
    TaskQueue taskQueue(ios);

    std::thread t([&]
    {
        boost::asio::io_service::work work(ios);
        ios.run();
    });

    std::thread u([&]
    {
        for (int i = 0; i != 100; ++i)
        {
            taskQueue.post([i]{ std::cout << i << std::endl; });
        }

        taskQueue.post([&]{ ios.stop(); });
    });

    t.join();
    u.join();
    std::cout << "Done." << std::endl;
}
