#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <condition_variable>

using namespace std;

class semaphore
{
private:
    std::mutex mx;
    std::condition_variable cv;
    unsigned long count;

public:
    semaphore() : count()
    {}

    void notify()
    {
        lock_guard<mutex> lk(mx);
        ++count;
        cv.notify_one();
    }

    void wait()
    {
        unique_lock<mutex> lk(mx);
        while(!count)
            cv.wait(lk);
        --count;
    }
};

struct master;
struct worker
{
    worker(int id) : id(id) {}

    void run(master& m) const;

    int id;
};

struct master
{
    mutable semaphore sem;

    master()
    {
        for (int i = 0; i<10; ++i)
            workers.emplace_back(i);

        for (auto& w: workers)
            threads.emplace_back(&worker::run, ref(w), ref(*this));
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
    vector<worker> workers;
    vector<thread> threads;
};

void worker::run(master& m) const
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
