#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

std::mutex mutexes[3];
std::mutex print_mutex;




struct DeferLock : std::unique_lock<std::mutex>
{
    DeferLock(int index) : std::unique_lock<std::mutex>(mutexes[index], std::defer_lock), retries() {}
    
    bool try_lock()
    {
        auto b = unique_lock::try_lock();
        retries += int(!b);
        return b;
    }
    
    int retries;
};


enum { num_threads = 6 };
static std::atomic<int> num_unstarted_threads{num_threads};

auto spin_wait = []{
    num_unstarted_threads--;
    while (num_unstarted_threads);
};
    

auto lock = [](int i, int j, int k)
{   
    spin_wait();    
    DeferLock a(i), b(j), c(k);    
    std::lock(a, b, c);        
    a.unlock(), b.unlock(), c.unlock();    
    
    std::lock_guard<std::mutex> lock_print_mutex(print_mutex);
    std::cout << "permutation: " << i <<  j << k
              << " retries: " << a.retries << ',' << b.retries << ',' << c.retries
              << std::endl;
};
    
int main()
{
    typedef std::thread t;
    
    std::thread threads[num_threads] = {
        t([]{ lock(0, 1, 2); }),
        t([]{ lock(0, 2, 1); }),
        t([]{ lock(1, 0, 2); }),
        t([]{ lock(1, 2, 0); }),
        t([]{ lock(2, 0, 1); }),
        t([]{ lock(2, 1, 0); })
    };
    
    for (auto&& t : threads) t.join();
}
