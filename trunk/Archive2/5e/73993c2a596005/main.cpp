#include <algorithm>
#include <deque>
#include <mutex>


template<typename T>
class SortedQueue
{        
public:
    SortedQueue() : mDirty(false) {}
    
private:
    // this is a helper used by the copy constructor
    SortedQueue(std::lock_guard<std::mutex>, const SortedQueue& rhs) :
        mQueue(rhs.mQueue),
        mDirty(rhs.mDirty)
    {
        // unlock on scope-exit (exception safe)
    }
    
public:
    // copy constructor
    SortedQueue(const SortedQueue& rhs) :
        SortedQueue(std::lock_guard<std::mutex>(rhs.mMutex), rhs) // delegate constructor (C++11)
    {
    }
    
    // copy-assignment operator
    SortedQueue& operator=(SortedQueue rhs) // local copy
    {
        mQueue = std::move(rhs.mQueue); // swap is also ok
        mDirty = std::move(rhs.mDirty);
        return *this;
    }

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
}