#include <deque>
#include <iostream>
#include <mutex>


template<typename T>
class Queue
{
public:

    // thread-safe push
    void push(T n)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mQueue.push_back(n);
    }
    
    // thread-safe pop
    T pop()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        T result = std::move(mQueue.back());
        mQueue.pop_back();
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
    mutable std::mutex mMutex; // non-copyable
};


int main()
{
    Queue<int> queue;
    queue.push(1);
    std::cout << "popped: " << queue.pop() << std::endl;
    
    // How to enable thread-safe copy-constructor?
    //Queue<int> copy = queue;
}
