#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <array>
#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <vector>


std::mutex m;

#define LOG(INFO) if (bool b = false) {} else for (std::lock_guard<std::mutex> lock(m); !b; ((std::cout << std::endl), b = true)) std::cout


struct CircularPool
{
    using size_type = long;


    template<typename T>
    struct Allocator
    {
        Allocator(CircularPool& inCircularPool) : mCircularPool(&inCircularPool) { }

        // TODO: implement allocator concept

        void* allocate(size_type n)
        { return mCircularPool->allocate(sizeof(T) * n); }

        void deallocate(void* p, size_type n)
        { return mCircularPool->deallocate(static_cast<char*>(p), sizeof(T) * n); }

        CircularPool* mCircularPool;
    };


    explicit CircularPool(int num_pages = 20) : mStorage(AllocatePage(num_pages), &std::free), mOffset(), mCapacity(num_pages * GetPageSize()) {}

    char* allocate(size_type n)
    {
        // TODO: debug checks to detect usage overflow

        // Note that the way the offset is calculated will cause the
        // first allocation to have an offset equal to its own size.
        // This seems weird, but it does prevent that allocation near
        // the end-of-storage would overflow the storage buffer.
        auto offset = (mOffset += align(n)) % mCapacity;
        return mStorage.get() + offset;
    }

    void deallocate(char*, size_type)
    {
        // null-operation
    }

private:
    static size_type align(size_type n)
    {
        auto r = n % sizeof(long double);
        return n + bool(r) * r;
    }

    static int GetPageSize()
    {
        return getpagesize();
    }


    static char* AllocatePage(size_type num_pages)
    {
        void* p;
        auto result = posix_memalign(&p, GetPageSize(), num_pages * GetPageSize());
        if (result != 0)
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }

        return static_cast<char*>(p);
    }


    std::unique_ptr<char, decltype(&std::free)> mStorage;
    std::atomic<std::uint64_t> mOffset{0};
    size_type mCapacity;
};




//
// Example program
//







struct TaskQueue
{
    explicit TaskQueue() : mIOService(), mThread([this]
    {
        boost::asio::io_service::work work(mIOService);
        mIOService.run();
    })
    {
    }

    ~TaskQueue()
    {
        post([this]{ mIOService.stop(); });
        mThread.join();
    }

    template<typename F>
    void post(F f)
    {
        mIOService.post(MakeTask(f, CircularPool::Allocator<char>{mPool}));
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

    CircularPool mPool;
    boost::asio::io_service mIOService;
    std::thread mThread;
};


int main()
{
    LOG(INFO) << "TEST";
    {
        TaskQueue taskQueue;
        boost::thread_group threads;

        for (int i = 0; i != 4; ++i)
        {
            threads.create_thread([i, &taskQueue]
            {
                for (int j = 0; j != 100; ++j)
                {
                    taskQueue.post([i, j]{ LOG(INFO) << "Thread=" << i << " Iteration=" << j; });
                    sched_yield();
                }

            });
        }

        LOG(INFO) << "START JOIN ALL";

        threads.join_all();
        LOG(INFO) << "FINISHED JOIN ALL" << std::endl;
    }

    LOG(INFO) << "END OF PROGRAM" << std::endl;

}
