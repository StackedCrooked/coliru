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
    
    std::deque<T> copyData() const
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return std::deque<T>(mQueue);
    }
    
    Queue<T>(const Queue<T> & rhs)
    {
        mQueue = rhs.copyData();
    }
    
    Queue<T>()
    {
    }
    
    Queue<T> operator=(const Queue<T> & rhs)
    {
        mQueue = rhs.copyData;
    }
    
private:
    std::deque<T> mQueue;
    mutable std::mutex mMutex; // non-copyable
};


int main()
{
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    
    
    // How to enable thread-safe copy-constructor?
    Queue<int> copy = queue;
    copy.push(1);
    
    std::cout << "queue popped: " << queue.pop() << std::endl;
    std::cout << "queue popped: " << queue.pop() << std::endl;
    
    std::cout << "copy popped: " << copy.pop() << std::endl;
    std::cout << "copy popped: " << copy.pop() << std::endl;
    std::cout << "copy popped: " << copy.pop() << std::endl;
}
