#include <boost/atomic.hpp>
#include <cassert>

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
    SpinLock x;
    x.lock();
    x.unlock();
    assert( x.try_lock() );
    assert( !x.try_lock() );
}