#include <atomic>
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "tbb/concurrent_queue.h"


typedef std::chrono::high_resolution_clock Clock;

std::mutex gMutex;
struct BufferedQueue
{
    BufferedQueue() :
        mQuit(false),
        mStartTime(Clock::now()),
        mRoundTripTime(),
        mThread([this]{ this->worker_thread(); })
    {
        mBuffer.reserve(100);
    }
    
    ~BufferedQueue()
    {
        Lock lock(mMutex);
        mQuit = true;
        mQueue.push(std::move(mBuffer));
        mBuffer.clear();
        mCondition.notify_all();
        lock.unlock();
        mThread.join();
    }
    
    void push(int n)
    {
        Lock lock(mMutex);
        mBuffer.push_back(n);
        if (mBuffer.size() == mBuffer.capacity())
        {
            mQueue.push(std::move(mBuffer));
            mBuffer.clear();
            mBuffer.reserve(100);
            auto new_time = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - mStartTime);
            mStartTime = Clock::now();
            mRoundTripTime = mRoundTripTime.count() ? (std::chrono::microseconds(9 * mRoundTripTime + 1 * new_time) / 10) : new_time;
            
            lock.unlock();
            
            std::unique_lock<std::mutex> lock(gMutex);
            std::cout << "new_time=" << new_time.count() << " roundtriptime=" << mRoundTripTime.count() << '\n';
        }
    }
    
    std::vector<int> pop()
    {
        Buffer buf;
        buf.reserve(100);
        for (;;)
        {
            Lock lock(mMutex);
            
            if (mQuit)
            {
                return buf;
            }
            
            mCondition.wait_for(lock, mRoundTripTime * 2);
            
            if (mQueue.try_pop(buf))
            {
                return buf;
            }
            
            if (mQuit)
            {
                return buf;
            }
        }
    }
    
private:
    void worker_thread()
    {
        for (;;)
        {
            Lock lock(mMutex);
            if (mQuit)
            {
                return;
            }
            
            mCondition.wait_for(lock, 2 * mRoundTripTime);
            
            
            if (mQuit)
            {
                return;
            }
            
            if (mBuffer.empty())
            {
                continue;
            }
            
            if (Clock::now() - mStartTime >= 2 * mRoundTripTime)
            {
                // size has not changed => assume end of input
                mQueue.push(std::move(mBuffer));
                mBuffer.reserve(100);
                mBuffer.clear();
            }
        }
    }
    
    typedef std::unique_lock<std::mutex> Lock;
    typedef std::vector<int> Buffer;
    
    bool mQuit;
    Clock::time_point mStartTime;
    std::chrono::microseconds mRoundTripTime;
    Buffer mBuffer;
    tbb::concurrent_queue<Buffer> mQueue;
    std::condition_variable mCondition;
    std::mutex mMutex;
    std::thread mThread;
};


std::atomic<bool> quit{false};
int main()
{
    BufferedQueue q;
    
    std::thread t([&]{
        for (;;)
        {
            auto v = q.pop();
            std::unique_lock<std::mutex> lock(gMutex);
            std::cout << "popped " << v.size() << '\n';
            if (quit)
            {
                return;
            }
        }
    });
    
    
    
    std::thread([]{ std::this_thread::sleep_for(std::chrono::seconds(1)); std::abort(); }).detach();
    
    for (int i = 0; i != 10001; ++i)
    {
        q.push(i);
        if (i % 1111 == 0)std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    //std::abort();
    quit = true;
    
    
    {
        
            std::unique_lock<std::mutex> lock(gMutex);
            std::cout << "QUIT" << std::endl;
    }
    t.join();
    {
        
            std::unique_lock<std::mutex> lock(gMutex);
            std::cout << "ALL OK" << std::endl;
    }
}

