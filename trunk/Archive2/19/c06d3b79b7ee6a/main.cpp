#include <atomic>
#include <cassert>
#include <condition_variable>
#include <mutex>
#include <future>
#include <iostream>
#include <vector>

std::atomic<int> perfcounter{0};

class Mutex
{
public:
    Mutex() : lockCounter(0) { }

    void lock()
    {
        if(lockCounter.fetch_add(1, std::memory_order_acquire)>0)
        {
            std::unique_lock<std::mutex> lock(internalMutex);
            perfcounter++;
            cv.wait(lock);
        }
    }

    void unlock()
    {
        if(lockCounter.fetch_sub(1, std::memory_order_release)>1)
        {
            cv.notify_one();
        }
    }


private:
    std::atomic<int> lockCounter;
    std::mutex internalMutex;
    std::condition_variable cv;
};

Mutex global;
int locksAcquired;
struct job 
{
    int id;
    void operator()() const
    {
        global.lock();
        std::cout << "JOB " << id << " acquired lock" << std::endl;
        locksAcquired++;
        global.unlock();
    }
};

int main()
{
    {
        std::vector< std::future<void> > alltasks;
        for ( int i = 0; i < 100;++i)
             alltasks.push_back( std::async( std::launch::async, job{i} ));
        // Join all the threads.
    }
    assert( locksAcquired == 100 );
    
    std::cout << "Contention counter: " << perfcounter << std::endl;
    
}
