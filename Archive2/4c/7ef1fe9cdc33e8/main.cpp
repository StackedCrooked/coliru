#include <mutex>

template<typename Mutex>
std::lock_guard<Mutex> lock_guard(Mutex& mutex)
{
    mutex.lock();
    return { mutex, std::adopt_lock };
}

int main()
{
    std::mutex mutex;
    auto&& g = lock_guard(mutex);
    (void)g;
}