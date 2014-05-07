#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <sstream>

std::mutex mutexes[3];

std::mutex print_mutex;

auto print = [](const std::string& s){
    std::lock_guard<std::mutex> lock_print_mutex(print_mutex);
    std::cout << s;
};

auto println = [](const std::string& s){
    print(s + '\n');
};

auto join = [](int i, int j, int k)
{
    std::stringstream ss;
    ss << i << ',' << j << ',' << k;
    return ss.str();
};




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





auto lock = [](int i, int j, int k)
{   
    // spin wait until all threads have started
    {
        static std::atomic<int> remaining{6}; 
        remaining--; while (remaining);
    }
    
    
    //println("started " + join(i, j, k));
    
    // create deferred locks
    DeferLock a(i), b(j), c(k);
    
    // lock them
    std::lock(a, b, c);        
    
    // unlock them
    a.unlock(), b.unlock(), c.unlock();    
    
    println("finished " + join(i, j, k) + " retries=" + join(a.retries, b.retries, c.retries));
};
    
int main()
{
    typedef std::thread t;
    
    std::thread threads[] = {
        t([]{ lock(0, 1, 2); }),
        t([]{ lock(0, 2, 1); }),
        t([]{ lock(1, 0, 2); }),
        t([]{ lock(1, 2, 0); }),
        t([]{ lock(2, 0, 1); }),
        t([]{ lock(2, 1, 0); })
    };
    
    for (auto&& t : threads) t.join();
}
