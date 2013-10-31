#include <mutex>

template <typename Pred>
inline std::unique_lock<std::mutex> lock_if(std::mutex& mutex, Pred&& predicate)
{
    std::unique_lock<std::mutex> lock(mutex, std::defer_lock);
	if (predicate()) lock.lock();
	return lock;
}
