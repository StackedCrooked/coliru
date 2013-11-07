#include <boost/range/algorithm.hpp>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>

class SpinLock
{
    boost::atomic_flag flag;
public:
    void lock()
    {
        while( flag.test_and_set(boost::memory_order_acquire) )
            ;
    }
    bool try_lock()
    {
        return !flag.test_and_set(boost::memory_order_acquire);
    }
    void unlock()
    {
        flag.clear(boost::memory_order_release);
    }
};

int main()
{
    using namespace std; using namespace boost;
    
    SpinLock lock;
    vector<thread> v;
    for(auto i = 0; i!=4; ++i)
        v.emplace_back([&lock, i]
        {
            for(auto j = 0; j!=16; ++j)
            {
                this_thread::yield();
                lock_guard<SpinLock> x(lock);
                cout << "Hello from " << i << flush << "\tj = " << j << endl;
            }
        });
    for(auto &t: v)
        t.join();
}