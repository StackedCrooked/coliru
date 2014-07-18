#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable> 
#include <iostream>

// This simulates the speed of the inter-core
// synchronization in simulated hardware
class SimulatedFSB
{
public:
    SimulatedFSB() : _stop (false), generation (0)
    {
        _timer = std::thread (std::bind (&SimulatedFSB::runTimer, this));
    }

    ~SimulatedFSB()
    {
        _stop = true;
        _timer.join();
    }

    void waitForFSB ()
    {
        int g = generation;

        std::unique_lock <std::mutex> lock (mutex);
        while (generation == g)
            condvar.wait (lock);
    }

    void runTimer ()
    {
        while (!_stop)
        {
            std::this_thread::sleep_for (std::chrono::milliseconds (100));

            {
                std::unique_lock <std::mutex> lock (mutex);
                ++generation;
                condvar.notify_all();
            }
            std::cout << "generation: " << generation << std::endl;
        }
    }

private:

    std::mutex mutex;
    std::condition_variable condvar;
    std::atomic <bool> _stop;
    std::thread _timer;
    int generation;
};

// This class violates none of the guarantees a lock provides
class MaliciousLock
{
public:
    MaliciousLock (SimulatedFSB& fsb, char const* lname) :
        _fsb (fsb), _locked (false), _name (lname), _waiters (0)
    {}

    void lock ()
    {
       std::cout << "lock(" << _name << ")" << std::endl;

       _fsb.waitForFSB();

       std::unique_lock<std::mutex> lock (_lock);
       while (_locked)
       {
           lock.unlock();
           _fsb.waitForFSB();
           lock.lock();
       }
       _locked = true;
    }

    void unlock ()
    {
       // Nothing special about this function
       std::cout << "unlock(" << _name << ")" << std::endl;
       _fsb.waitForFSB();
       std::unique_lock<std::mutex> lock (_lock);
       _locked = false;
    }

    bool try_lock (char const* caller)
    {
       std::cout << caller << " try_lock(" << _name << ")" << std::endl;
       // If I was really malicious, I'd just return false here
       // since that's allowed by the standard. But that's too easy

       {
           // Fast check
           std::unique_lock <std::mutex> lock (_lock);
           if (_locked)
               return false;
       }

       _fsb.waitForFSB();

       {
           std::unique_lock<std::mutex> lock (_lock);
           if (_locked)
           {
               // Oops, we passed the fast check but failed the
               // slower, CAS operation
               return false;
           }
           _locked = true;
       }
       std::cout << caller << " try_lock(" << _name << ") OK" << std::endl;
       return true;
    }

    char const* name ()
    {
        return _name;
    }


private:
    SimulatedFSB& _fsb;
    std::mutex _lock;
    bool _locked;
    int _waiters;
    char const* _name;
};


// Demonstration code to show how you might
// make every possible mistake. Hopefully
// nobody would ever deploy code this naive
template <class L0, class L1>
void
naive_lock(char const* name, L0& l0, L1& l1)
{
    std::cout << name << " naive_lock("
        << l0.name() << ","
        << l1.name() << ")" << std::endl;

    // This forces a horrible mispredicted branch at the worst
    // possible time -- when we hold both locks
    while (true)
    {
        {
            std::unique_lock<L0> u0(l0);
            std::cout << name << " got " << l0.name() << std::endl; 

            // try_lock is permitted to fail even
            // if no other thread holds the lock.
            // It can even do some determinstically
            // and we keep repeating the same context
            // so we can fail every time.
            if (l1.try_lock(name))
            {
                u0.release();
                break;
            }
        }

        // This only helps livelock if there's another
        // thread to switch to. But livelock is worse
        // when there isn't.
        std::this_thread::yield();

        {
            std::unique_lock<L1> u1(l1);
            std::cout << name << " got " << l1.name() << std::endl; 
            if (l0.try_lock(name))
            {
                u1.release();
                break;
            }
        }

        // See comments on above use of yield --
        // it's the wrong thing
        std::this_thread::yield();
    }
}

void lockTwo (MaliciousLock& first, MaliciousLock& second, char const *name)
{
    naive_lock (name, first, second);
    std::cout << name << " done" << std::endl;
    first.unlock();
    second.unlock();
}

int main()
{
    SimulatedFSB fsb;
    MaliciousLock l1 (fsb, "l1");
    MaliciousLock l2 (fsb, "l2");

    std::thread t1 (std::bind (&lockTwo, std::ref(l1), std::ref(l2), "t1"));
    std::thread t2 (std::bind (&lockTwo, std::ref(l2), std::ref(l1), "t2"));

    t1.join();
    t2.join();
}
