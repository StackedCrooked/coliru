#include <iostream>
#include <algorithm>
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <random>

class thread_pool
{
private:
    std::queue<std::function<void()>> work;
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic_bool shutdown;
    
    void thread_proc()
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (true)
        {
            cv.wait(lock, [this](){ return shutdown || !work.empty(); });
            if (work.empty())
                break;
            
            auto fn = work.front();
            work.pop();
            lock.unlock();
            fn();

            // relatch for next go-arond
            lock.lock();
        }
    };
    
public:
    thread_pool(unsigned int n = std::thread::hardware_concurrency())
    {
        std::generate_n(std::back_inserter(threads), n,
            [this]() { return std::thread(std::bind(&thread_pool::thread_proc, this));});
    }
    
    ~thread_pool()
    {
        shutdown = true;
        cv.notify_all();
        std::for_each(threads.begin(), threads.end(),
                [](std::thread& t){ t.join(); });
    }
    
    void push(std::function<void()> fn)
    {
        std::unique_lock<std::mutex> lock(mtx);
        work.push(fn);
        cv.notify_one();
    }
};

// sample work function that generates a vector of
//  one million random values from 1..1000000, then
//  sorts them.
void some_work()
{
    static std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(1,1000000);
    
    std::vector<int> vec;
    std::generate_n(std::back_inserter(vec), 1000000,
            [&](){ return dist(rng); });
    std::sort(vec.begin(), vec.end());
    
    static std::mutex mtx;
    static std::atomic_int n;
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << ++n << " - finished sorting " << vec.size() << " items.\n";
}

int main()
{
    thread_pool tp;
    
    for (int i=0; i<25; ++i)
        tp.push(some_work);
        
    return 0;
}