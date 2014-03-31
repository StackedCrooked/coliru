#include <tbb/concurrent_queue.h>
#include <atomic>
#include <iostream>
#include <memory>
#include <thread>
#include <assert.h>


template<typename T>
struct Batch
{
    enum { Capacity = 10 };
    
    Batch() : items(), size() {}
    
    bool push(T t)
    {
        items[size++] = std::move(t);
        return size == Capacity;
    }
    
    
    bool pop(T& t)
    {
        if (size == 0)
        {
            return false;
        }
        
        t = std::move(items[Capacity - size]);
        size--;
        return true;
    }
    
    T items[Capacity];
    uint8_t size;
};


template<typename T>
struct ConcurrentBatchQueue
{
    ConcurrentBatchQueue(std::size_t capacity) :
        mQueue(),
        mBatchPool(new Batch<T>[capacity + 1]),
        mIndex(1),
        mPoppedBatch(mBatchPool.get())
    {
        mQueue.set_capacity(capacity);
    }
    
    void push(T t)
    {
        auto& batch = mBatchPool.get()[mIndex];
        if (batch.push(std::move(t)))
        {
            flush();
        }
    }
    
    void flush()
    {
        auto& current_batch = mBatchPool[mIndex];
        mQueue.push(&current_batch);
        current_batch = Batch<T>();
        mIndex = (mIndex + 1) % mQueue.capacity();
    }
    
    bool pop(T& t)
    {
        if (mPoppedBatch->pop(t))
        {
            return true;
        }
        
        mQueue.pop(mPoppedBatch);
        
        return mPoppedBatch->pop(t);
    }
    
    tbb::concurrent_bounded_queue<Batch<T>*> mQueue;
    std::unique_ptr<Batch<T>[]> mBatchPool;
    std::size_t mIndex;
    
    char padding[128];
    
    Batch<T>* mPoppedBatch;
    
};


int main()
{

    ConcurrentBatchQueue<int> q(100);
    
    std::atomic<bool> quit(false);
        
    std::thread producer([&]{
        int n = 0;
        while (!quit) {
            q.push(n++);
        }
    });
    
    std::thread consumer([&]{
        while (!quit) {
            int n;
            while (q.pop(n)) {
                std::cout << n << ' ';
            }
            sched_yield();
        }
    });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    quit = true;
    producer.join();
    consumer.join();
}