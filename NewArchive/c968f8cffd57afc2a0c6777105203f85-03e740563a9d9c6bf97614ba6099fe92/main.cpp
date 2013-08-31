#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <condition_variable>

using namespace std;

class semaphore 
{ // see http://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads
    std::mutex mx;
    std::condition_variable cv;
    unsigned long count;
public:
    semaphore() : count() {} 
    void notify();
    void wait();
};

static void run(int id, struct master& m);

struct master
{
    mutable semaphore sem;

    master()
    {
        for (int i = 0; i<10; ++i)
            threads.emplace_back(run, i, ref(*this));
    }

    ~master() {
        for(auto& th : threads) if (th.joinable()) th.join(); 
        std::cout << "done\n";
    }

    void drive()
    {
        // do wakeups
        for (unsigned i = 0; i<threads.size(); ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(rand()%100));
            sem.notify();
        }
    }

  private:
    vector<thread> threads;
};

static void run(int id, master& m)
{
    m.sem.wait();
    {
        static mutex io_mx;
        lock_guard<mutex> lk(io_mx);
        cout << "signaled: " << id << "\n";
    }
}

int main()
{
    master instance;
    instance.drive();
}

/// semaphore members
void semaphore::notify()
{
    lock_guard<mutex> lk(mx);
    ++count;
    cv.notify_one();
}

void semaphore::wait()
{
    unique_lock<mutex> lk(mx);
    while(!count)
        cv.wait(lk);
    --count;
}
