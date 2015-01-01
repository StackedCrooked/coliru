
// NOTE:
// - TaskQueue::dispatch_impl: packaged_task with allocator_arg_t
// - TaskQueue::Task::Task: std::allocate_shared is used instad of std::make_shared.
// - All the other code is supporting.

#include <boost/container/flat_map.hpp>
#include <tbb/concurrent_queue.h>
#include <tbb/spin_mutex.h>
#include <cassert>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <scoped_allocator>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cxxabi.h>



std::string Demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
    }
}




enum LogLevel { Low, High };


std::ostream& operator<<(std::ostream& os, LogLevel ll)
{
    return os << (ll == Low ? "Low" : "High");
}


enum { gLogLevel = High };


struct Log : std::stringstream
{
    Log(LogLevel inLogLevel) : mLogLevel(inLogLevel) {}

    ~Log()
    {
        static std::mutex fMutex;
        std::lock_guard<std::mutex> lock(fMutex);
        std::cout << this->str() << std::endl;
    }

    LogLevel mLogLevel;
};


#define LOG(level) if (level < gLogLevel) ; else Log(level) << ' '



// Create STL-compatible allocator for objects of type T using custom storage type.
template <typename Storage>
struct Adaptor
{
    template<typename T>
    struct Allocator
    {
        typedef T * pointer;
        typedef const T * const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        template<typename U>
        struct rebind
        {
            typedef Allocator<U> other;
        };

        Allocator() : mStorage() {}

        Allocator(Storage& inStorage) :
            mStorage(&inStorage)
        {
            assert(mStorage);
        }

        template<typename U>
        Allocator(const Allocator<U>& rhs) :
            mStorage(rhs.mStorage)
        {
            assert(mStorage);
        }

        template<typename U>
        Allocator& operator=(const Allocator<U>& rhs)
        {
            assert(mStorage);
            mStorage = rhs.mStorage;
            return *this;
        }

        ~Allocator()
        {
        }

        const T* address(const T& s) const { return &s; }
        T* address(T& r) const { return &r; }

        size_t max_size() const { return std::size_t(-1); }

        bool operator==(const Allocator& rhs) const { return mStorage == rhs.mStorage; }
        bool operator!=(const Allocator& rhs) const { return mStorage != rhs.mStorage; }

        template<typename U, typename ...Args>
        void construct(U* p, Args&& ...args) const
        {
            assert(p);
            new (p) U(std::forward<Args>(args)...);
        }

        void destroy(T * const p) const
        {
            p->~T();
        }

        T * allocate(size_t block_size) const
        {
            Log(High) << "Allocation size=" << (block_size * sizeof(T)) << " bytes. Type=" << Demangle(typeid(T).name());
            assert(block_size);
            assert(mStorage);
            return static_cast<T*>(mStorage->allocate(block_size * sizeof(T)));
        }

        void deallocate(T * const p, const size_t n) const
        {
            assert(mStorage);
            mStorage->deallocate(p, n * sizeof(T));
        }

        template <typename U>
        T * allocate(const size_t n, const U*) const
        {
            return this->allocate(n);
        }

        //using propagate_on_container_copy_assignment = std::true_type;
        //using propagate_on_container_move_assignment = std::true_type;

        Storage* mStorage;
    };
};


/**
 * FixedFreeListPool is a pool that allocates fixed-size segments.
 * - allocate pops a block from the free-list (or uses malloc if empty)
 * - deallocate pushes the block on the free-list
 *
 * Requires less CPU than other pools but also makes no effort to have good memory locality.
 *
 * Recommended for large block sizes.
 */
struct FixedFreeListPool
{
    FixedFreeListPool() : mAllocs()
    {
    }

    FixedFreeListPool(const FixedFreeListPool&) = delete;
    FixedFreeListPool& operator=(const FixedFreeListPool&) = delete;

    FixedFreeListPool(FixedFreeListPool&& rhs) noexcept :
        mSegments(std::move(rhs.mSegments)),
        mAllocs(std::move(rhs.mAllocs)),
        mBlockSize(std::move(rhs.mBlockSize))
    {
    }

    FixedFreeListPool& operator=(FixedFreeListPool&& rhs) noexcept
    {
        mSegments = std::move(rhs.mSegments);
        mAllocs = std::move(rhs.mAllocs);
        mBlockSize = std::move(rhs.mBlockSize);
        return *this;
    }

    ~FixedFreeListPool()
    {
        if (mSegments.size() > 0) Log(High) << "FixedFreeListPool: segment_count=" << mSegments.size() << " block_size=" << mBlockSize << " total_size=" << (mSegments.size() * mBlockSize) << " bytes";
        while (!mSegments.empty())
        {
            free(mSegments.back());
            mSegments.pop_back();
        }
    }

    void* allocate(std::size_t n)
    {
        assert(mBlockSize == 0 || mBlockSize == n);
        mBlockSize = n;

        if (mSegments.empty())
        {
            Log(High) << "Allocating new segment of " << n << " bytes";
            mAllocs += n;
            return malloc(n);
        }

        Log(High) << "Reusing existing segment of " << n << " bytes";
        auto result = mSegments.back();
        mSegments.pop_back();
        return result;
    }

    void deallocate(void* data, std::size_t n)
    {
        assert(mBlockSize == 0 || mBlockSize == n);
        mSegments.push_back(data);
    }

    std::vector<void*> mSegments;
    uint32_t mAllocs;
    uint32_t mBlockSize = 0;
};


/**
 * FixedChunkingPool is a pool that allocates blocks grouped in chunks.
 * It requires more CPU than FixedFreeListPool but provides better memory locality.
 *
 * This is recommended for small block sizes.
 */
struct FixedChunkingPool
{
    FixedChunkingPool() : mPreviousChunkCount()
    {
    }

    FixedChunkingPool(FixedChunkingPool&&) = default;
    FixedChunkingPool& operator=(FixedChunkingPool&&) = default;

    FixedChunkingPool(const FixedChunkingPool&) = delete;
    FixedChunkingPool& operator=(const FixedChunkingPool&) = delete;

    ~FixedChunkingPool()
    {
        if (!mChunks.empty())
        {
            LOG(Low) << "FixedPool: destroying " << mChunks.size() << " chunks.";
            while (!mChunks.empty())
            {
                Chunk& chunk = mChunks.back();
                chunk.cleanup();
                mChunks.pop_back();
            }
        }
    }

    void* allocate(std::size_t block_size)
    {
        if (mChunks.empty()) init(block_size);
        Chunk* chunk = findAvailableChunk();
        if (!chunk)
        {
            mChunks.resize(mChunks.size() + 1);

            mLastFree = nullptr;
            chunk = &mChunks.back();
            chunk->init(block_size);

            if (mChunks.size() >= 2 * mPreviousChunkCount)
            {
                mPreviousChunkCount = mChunks.size();
                LOG(Low) << "FixedChunkingPool(" << this << ") is currently managing " << mPreviousChunkCount << " chunks each containing 255 blocks of " << block_size << " bytes. Total managed size=" << (mPreviousChunkCount * 255);
            }
        }
        LOG(High) << "Allocating " << block_size << " bytes from chunk " << (void*)chunk;
        
        mLastAlloc = chunk;
        return chunk->allocate(block_size);
    }

    void deallocate(void* data, std::size_t block_size)
    {
        assert(!mChunks.empty());
        if (!mLastFree || !mLastFree->contains(data, block_size))
        {
            for (Chunk& chunk : mChunks)
            {
                if (chunk.contains(data, block_size))
                {
                    mLastFree = &chunk;
                    goto resume;
                }
            }
            LOG(Low) << "ChunkBasedFixedPool::deallocate: there no parent chunk for ptr=" << data << " size=" << block_size;
            assert(!"Invalid free");
        }

        resume:
        mLastFree->deallocate(data, block_size);
    }

private:
    struct Chunk
    {
        void init(std::size_t block_size)
        {
            auto chunk_size = block_size * std::uint8_t(-1);

            LOG(High) << "Allocated chunk of " << chunk_size << " bytes which is divided into " << int(std::uint8_t(-1)) << " blocks of " << block_size << " bytes each";
            mData = static_cast<uint8_t*>(malloc(chunk_size));
            mFirstFreeBlock = 0;
            mNumFreeBlocks = std::uint8_t(-1);

            for (std::uint8_t i = 0; i != std::uint8_t(-1); ++i)
            {
                getByIndex(block_size, i)[0] = i + 1;
            }
        }

        void cleanup()
        {
            free(mData);
            mData = nullptr;
        }

        void* allocate(std::size_t block_size)
        {
            assert(mNumFreeBlocks);
            if (!mNumFreeBlocks) return nullptr;
            auto result = getByIndex(block_size, mFirstFreeBlock);
            mFirstFreeBlock = result[0];
            --mNumFreeBlocks;
            return result;
        }

        void deallocate(void* data, std::size_t block_size)
        {
            assert(mData <= data && data <= mData + block_size * std::uint8_t(-1));
            auto block = static_cast<std::uint8_t*>(data);
            block[0] = mFirstFreeBlock;
            mFirstFreeBlock = getIndexOf(block_size, block);
            ++mNumFreeBlocks;
        }

        bool contains(void* data, std::size_t block_size)
        {
            return mData <= data && data < mData + std::uint8_t(-1) * block_size;
        }

        bool isFull() const
        {
            return mNumFreeBlocks == 0;
        }

        std::uint8_t* getByIndex(std::size_t block_size, std::size_t object_index)
        {
            assert(object_index <= std::uint8_t(-1));
            return mData + block_size * object_index;
        }

        std::size_t getIndexOf(std::size_t block_size, std::uint8_t* block)
        {
            auto difference = block - mData;
            assert(difference % block_size == 0);
            auto result = difference / block_size;
            assert(result <= std::uint8_t(-1));
            return result;
        }

        std::uint8_t* mData;
        std::uint8_t mFirstFreeBlock;
        std::uint8_t mNumFreeBlocks;
    };

    Chunk* findAvailableChunk()
    {
        if (!mLastAlloc->isFull())
        {
            return mLastAlloc;
        }

        for (Chunk& chunk : mChunks)
        {
            if (!chunk.isFull())
            {
                return &chunk;
            }
        }

        return nullptr;
    }

    void init(std::size_t block_size)
    {
        mChunks.resize(1);
        for (Chunk& chunk : mChunks)
        {
            chunk.init(block_size);
        }
        mLastAlloc = &mChunks.front();
        mLastFree = &mChunks.front();
        mChunkSize = block_size * uint8_t(-1);

        LOG(Low) << "FixedPool was created for objects of size " << block_size;
    }

    std::vector<Chunk> mChunks;
    Chunk* mLastAlloc;
    Chunk* mLastFree;
    uint32_t mChunkSize;
    uint32_t mPreviousChunkCount;
};


struct FlexiblePool
{
    FlexiblePool()
    {
    }

    FlexiblePool(const FlexiblePool&) = delete;
    FlexiblePool& operator=(const FlexiblePool&) = delete;

    FlexiblePool(FlexiblePool&&) = default;
    FlexiblePool& operator=(FlexiblePool&&) = default;

    ~FlexiblePool()
    {
        if (mFixedChunkingPools.size() > 1)
        {
            LOG(High) << "FlexiblePool: destroying " << mFixedChunkingPools.size() << " fixed-size pools.";
        }
    }

    void* allocate(std::size_t block_size)
    {
        LOG(Low) << "Allocate " << block_size;

        tbb::spin_mutex::scoped_lock lock(mMutex);
        if (block_size <= 128)
        {
            FixedChunkingPool& pool = mFixedChunkingPools[block_size];
            return pool.allocate(block_size);
        }
        else
        {
            FixedFreeListPool& pool = mFixedFreeListPools[block_size];
            return pool.allocate(block_size);
        }
    }

    void deallocate(void* data, std::size_t block_size)
    {
        LOG(Low) << "Deallocate " << block_size;

        tbb::spin_mutex::scoped_lock lock(mMutex);
        if (block_size <= 128)
        {
            FixedChunkingPool& pool = mFixedChunkingPools[block_size];
            pool.deallocate(data, block_size);
        }
        else
        {
            FixedFreeListPool& pool = mFixedFreeListPools[block_size];
            return pool.deallocate(data, block_size);
        }
    }

    tbb::spin_mutex mMutex;
    boost::container::flat_map<int, FixedFreeListPool> mFixedFreeListPools;
    boost::container::flat_map<int, FixedChunkingPool> mFixedChunkingPools;
};



// NOTE: scoped_allocator_adaptor should be used when nested std::containers are involved
//template<typename T> using Allocator = std::scoped_allocator_adaptor<Adaptor<FlexiblePool>::Allocator<T>>;

// NOTE: For simplicity not using scoped_allocator_adaptor here.
template<typename T> using Allocator = Adaptor<FlexiblePool>::Allocator<T>;


/// A small collection of very convenient type traits.
/// Based on R. Martinho Fernandes's articles on flamingdangerzone.com.


//! Invoke<T> is a shorter way to say `typename T::type`
template<typename T>
using Invoke = typename T::type;


//! EnableIf enables a shorter syntax for std::enable_if
template <typename Condition, typename T = void>
using EnableIf = Invoke<std::enable_if<Condition::value, T>>;


//! DisableIf is same as EnableIf but for negative testing
template <typename Condition, typename T = void>
using DisableIf = Invoke<std::enable_if<!Condition::value, T>>;


//! Decay<T> removes constness and reference from T.
template <typename T>
using Decay = Invoke<std::decay<T>>;


//! Checks if two types are identical after removing their const/ref attributes.
template <typename T, typename U>
struct IsRelated : std::is_same<Decay<T>, Decay<U>> {};



template<typename T>
struct TaskQueue
{
    TaskQueue() :
        mObj(),
        mThread([=]{ consume(); })
    {
    }

    struct QuitException : std::runtime_error
    {
        QuitException() : std::runtime_error("QuitException") {}
        ~QuitException() throw() {}
    };

    ~TaskQueue()
    {
        if (!mQuit)
        {
            stop();
        }
    }

    void stop()
    {
        if (mQuit)
        {
            return;
        }

        mQuit = true;
        try
        {
            dispatch_impl<void>(Task());
        }
        catch (const std::exception& e)
        {
            LOG(Low) << "~Shared: caught: " << e.what();
        }
        mThread.join();
    }

    template<typename F>
    auto dispatch(F&& f) -> decltype(f(std::declval<T&>()))
    {
        if (mQuit)
        {
            throw std::runtime_error("Quit");
        }
        using R = decltype(f(std::declval<T&>()));
        return dispatch_impl<R>(std::forward<F>(f));
    }

private:
    TaskQueue(const TaskQueue&) = delete;
    TaskQueue& operator=(const TaskQueue&) = delete;

    template<typename R, typename F>
    auto dispatch_impl(F&& f) -> R
    {
        // std::packaged_task allocation using allocator
        Allocator<char> alloc(mStorage);
        std::packaged_task<R(T&)> task(std::allocator_arg, alloc, std::forward<F>(f));
        auto fut = task.get_future();

        // shared_ptr allocation also using allocator
        mQueue.push(Task(std::allocator_arg, alloc, std::move(task)));
        return fut.get();
    }

    struct Task
    {
        Task() =  default;

        template<typename Alloc, typename F, typename = DisableIf<IsRelated<Task, F>>>
        Task(std::allocator_arg_t, Alloc alloc, F&& f) : mImpl(std::allocate_shared<Impl<Decay<F>>>((typename Alloc::template rebind<Impl<Decay<F>>>::other)(alloc), std::forward<F>(f))) {}

        ~Task() = default;

        Task(Task&& rhs) noexcept = default;
        Task& operator=(Task&& rhs) noexcept = default;

        Task(const Task& rhs) noexcept :
            mImpl(std::move(rhs.mImpl))
        {
        }

        Task& operator=(const Task& rhs) noexcept
        {
            mImpl = std::move(rhs.mImpl);
            return *this;
        }


        explicit operator bool() const
        {
            return !!mImpl;
        }

        void operator()(T& t)
        {
            if (!mImpl) throw QuitException();
            (*mImpl)(t);
        }

        struct ImplBase
        {
            virtual ~ImplBase() {}

            virtual void operator()(T& t) = 0;
        };

        template<typename F>
        struct Impl : ImplBase
        {
            template<typename FF>
            Impl(FF&& ff) : f(std::forward<FF>(ff)) {}

            virtual void operator()(T& t) override final
            {
                f(t);
            }

            F f;
        };

        mutable std::shared_ptr<ImplBase> mImpl;
    };

    void consume()
    {
        Task task;

        for (;;)
        {
            if (mQuit) { return; }

            mQueue.pop(task);

            if (!task) { return; }

            task(mObj);
        }
    }

    std::atomic<bool> mQuit{false};
    FlexiblePool mStorage;
    tbb::concurrent_bounded_queue<Task> mQueue;
    T mObj;
    std::thread mThread;
};



int main()
{
    std::thread([]{ std::this_thread::sleep_for(std::chrono::milliseconds(10000));  LOG(Low) <<  "FORCE QUIT"; std::abort(); }).detach();
    TaskQueue<int> task_queue;
    LOG(Low) << __LINE__;
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::future<void>> futures;
    std::atomic<int> started{0};
    std::atomic<int> stopped{0};
    std::atomic<long> sum{0};
    futures.reserve(30);
    for (auto i = 0ul; i != futures.capacity(); ++i)
    {
        LOG(Low) << "i=" << i;
        auto thread_index = i;
        futures.push_back(std::async(std::launch::async, [&]
        {
            std::this_thread::sleep_until(start_time + std::chrono::milliseconds(10));
            auto started_counter = ++started;
            LOG(Low) << "started=" << started_counter << " stopped=" << started_counter;

            try
            {
                for (int i = 0; i != 100; ++i)
                {
                    sum += task_queue.dispatch([=](int& n){ return n += 1; });
                }
            }
            catch (const std::exception& e)
            {
                LOG(Low) << "Thread " << thread_index << " caught " << e.what();
            }


            auto stopped_counter = ++stopped;
            LOG(Low) << "started=" << started << " stopped=" << stopped_counter << " sum=" << sum;
        }));
    }

    for (auto&& fut : futures)
    {
        fut.get();
    }

    LOG(Low) << "End of program.";
}
