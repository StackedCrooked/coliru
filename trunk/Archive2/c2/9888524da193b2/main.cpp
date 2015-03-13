#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <array>
#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <vector>



struct Pool
{
    using size_type = std::uint32_t;

    explicit Pool() : mStorage()
    {
    }

    char* allocate(size_type n)
    {
        return mStorage.malloc(align(n));
    }

    void deallocate(char* p, size_type n)
    {
        // Deallocate? Never!
        mStorage.free(p, align(n));
    }

private:
    static size_type align(size_type n)
    {
        auto r = n % sizeof(long double);
        return n + bool(r) * r;
    }

    struct Storage
    {
        Storage(size_type num_pages = 100) :
            mData(AllocatePage(num_pages), &std::free),
            mCapacity(num_pages * GetPageSize())
        {
        }

        Storage(const Storage&) = default;
        Storage& operator=(const Storage&) = default;

        ~Storage()
        {
            printStats();
            assert(mAllocated == mFreed);
        }

        char* data()
        {
            return mData.get();
        }

        char* malloc(size_type n)
        {
            size_type allocated = mAllocated += n;
            while (mCapacity + mFreed < allocated)
            {
                sched_yield();
                LOG(INFO) << "YIELD";
            }
            printStats();
            return data() + allocated % mCapacity;
        }

        void free(char*, size_type n)
        {
            assert(n > 0);
            mFreed += n;
            //printStats();

        }

        void printStats() const
        {
            long allocated = mAllocated;
            long freed = mFreed;
            long available = mCapacity + freed - allocated;

            assert(available >= 0);
            assert(freed >= 0);

            LOG(INFO)
                << " capacity=" << mCapacity
                << " allocated=" << allocated
                << " freed=" << freed
                << " available=" << available
                << '\n';
        }

    private:
        static size_type GetPageSize()
        {
            return sysconf(_SC_PAGESIZE);
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

        std::unique_ptr<char, decltype(&std::free)> mData;
        std::atomic<size_type> mAllocated{0};
        std::atomic<size_type> mFreed{0};
        const size_type mCapacity;
    };

    Storage mStorage;
};



template<typename T>
struct Allocator
{
    using Traits = std::allocator_traits<Allocator<T>>;

    using value_type = T;
    using size_type = Pool::size_type;

    Allocator(Pool& inPool) : pool_(&inPool)
    {
        // Check if std::allocator_traits works.
        static_assert(std::is_same<typename Traits::size_type , size_type >::value, "");
        static_assert(std::is_same<typename Traits::value_type, value_type>::value, "");
        static_assert(std::is_same<typename Traits::pointer   , T*        >::value, "");
    }

    bool operator==(const Allocator& rhs) const
    {
        return pool_ == rhs.pool_;
    }

    template<typename U>
    bool operator==(const Allocator<U>&) const
    {
        return false;
    }

    T* allocate(size_type n)
    {
        return static_cast<T*>(pool_->allocate(sizeof(T) * n));
    }

    void deallocate(T* p, size_type n)
    {
        return pool_->deallocate(static_cast<char*>(static_cast<void*>(p)), sizeof(T) * n);
    }

private:
    Pool* pool_;
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
        mIOService.post(MakeTask(f, Allocator<char>{mPool}));
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

    Pool mPool;
    boost::asio::io_service mIOService;
    std::thread mThread;
};


int main()
{
    {
        TaskQueue taskQueue;
        boost::thread_group threads;

        for (int i = 0; i != 10; ++i)
        {
            threads.create_thread([i, &taskQueue]
            {
                for (int j = 0; j != 100; ++j)
                {
                    taskQueue.post([i, j]{ LOG(INFO) << "Thread=" << i << " Iteration=" << j; });
                }

            });
        }

        LOG(INFO) << "START JOIN ALL";

        threads.join_all();
        LOG(INFO) << "FINISHED JOIN ALL" << std::endl;
    }

    LOG(INFO) << "END OF PROGRAM" << std::endl;

}
