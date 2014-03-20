#include <mutex>

template<typename Mutex>
struct lock_guard_aggregate {
    std::lock_guard<Mutex> lock_guard;
};

template<typename Mutex>
lock_guard_aggregate<Mutex> lock_guard(Mutex& mutex)
{
    mutex.lock();
    return { { mutex, std::adopt_lock } };
}

int main()
{
    std::mutex mutex;
    auto&& g = lock_guard(mutex);
    (void)g;
}