#include <algorithm>
#include <deque>
#include <iostream>
#include <mutex>


template<typename T>
class SortedQueue
{
public:
    SortedQueue() : mDirty(false) {}

    // thread-safe push
    // sets dirty flag
    void push(T n)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mQueue.push_back(n);
        mDirty = true;
    }
    
    // thread-safe pop
    // will first sort the queue if the dirty flag is set
    T pop()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mDirty)
        {
            std::sort(mQueue.begin(), mQueue.end());
            mDirty = false;
        }
        T result = std::move(mQueue.front());
        mQueue.pop_front();
        return result;
    }
    
    std::size_t size() const
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return mQueue.size();
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return mQueue.empty();
    }
    
private:
    std::deque<T> mQueue;
    mutable bool mDirty;
    mutable std::mutex mMutex; // non-copyable
};


int main()
{
    SortedQueue<int> queue;
    queue.push(1);
    queue.push(9);
    queue.push(3);
    queue.push(7);
    
    
    while (!queue.empty())
    {
        std::cout << queue.pop() << ' ';
    }
    
    // How to enable thread-safe copy-constructor?
    //Queue<int> copy = queue;
}
