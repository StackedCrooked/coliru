#ifndef TSQUEUE_H
#define TSQUEUE_H

#include <queue>
#include <mutex>

template <typename T>
class TSQueue
{
    mutable std::mutex mutex;
    std::queue<T> queue;

public:
    template <typename R>
    void push(R&& t)
    {
        mutex.lock();
        queue.push(std::forward<R>(t));
        mutex.unlock();
    }

    T pop()
    {
        mutex.lock();
        T ret = std::move(queue.front());
        queue.pop();
        mutex.unlock();
        return ret;
    }

    bool empty() const
    {
        mutex.lock();
        bool ret = queue.empty();
        mutex.unlock();
        return ret;
    }
};

#endif

int main()
{
    return 0;
}
