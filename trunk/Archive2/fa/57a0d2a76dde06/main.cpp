#include <atomic>
#include <mutex>
#include <iostream>
#include <thread>
#include <type_traits>


template<typename T, std::size_t Capacity>
class CircularQueue
{
public:
    CircularQueue() : mBegin(), mPadding1(), mEnd(), mPadding2(), mBuffer()
    {
    }

    std::size_t unsafe_size() const
    {
        return mEnd - mBegin;
    }

    template<typename U>
    bool try_push(U&& u)
    {
        std::size_t old_end = mEnd.load(std::memory_order_relaxed);
        if (old_end < Capacity + mBegin)
        {
            new (&mBuffer[old_end % Capacity]) T(std::forward<U>(u));
            mEnd.store(old_end + 1, std::memory_order_release);
            return true;
        }
        return false;
    }

    bool try_pop(T& t)
    {
        std::size_t old_begin = mBegin.load(std::memory_order_relaxed);
        if (old_begin < mEnd)
        {
            t = std::move(*static_cast<T*>(static_cast<void*>(&mBuffer[old_begin % Capacity])));
            mBegin.store(old_begin + 1, std::memory_order_release);
            return true;
        }
        return false;
    }

private:
    std::atomic<std::size_t> mBegin;
    char mPadding1[128 - sizeof(mBegin)];

    std::atomic<std::size_t> mEnd;
    char mPadding2[128 - sizeof(mEnd)];

    using Storage = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
    Storage mBuffer[Capacity];
};



CircularQueue<int, 100000000> queue;
long queue_padding[16];

const auto start_time = std::chrono::steady_clock::now(); char padding0[128 - sizeof(start_time)];


std::atomic<long> pushed; char padding1[128 - sizeof(pushed)];
std::atomic<long> popped; char padding2[128 - sizeof(popped)];

enum { num_iterations = 4000000 };

char padding[100];
std::mutex mutex;

auto log = [](long pushed, long popped, long i)
{
    if (i % (num_iterations / 50) == 0)
    {
        std::cout << "pushed=" << pushed << " popped=" << popped << " queue.size=" << queue.unsafe_size() << " i=" << i << std::endl;
    }
};


char padding_l[100];
long l = 0;


int main()
{
    auto producer_task = []{
        std::this_thread::sleep_until(start_time + std::chrono::seconds(1));
        for (int i = 0; i != num_iterations; ++i)
        {
            if (l % 2 == 0) { log(pushed, popped, i); l++; }
            if (queue.try_push(i)) pushed++;
        }
    };

    auto consumer_task = []{
        std::this_thread::sleep_until(start_time + std::chrono::seconds(1));
        for (int i = 0; i != num_iterations; ++i)
        {
            if (l % 2 == 1) { log(pushed, popped, i); l++; }
            if (queue.try_pop(i)) popped++;
        }
    };

    std::thread c1(consumer_task);
    std::thread p1(producer_task);
    p1.join();
    c1.join();

    log(pushed, popped, num_iterations);
}
