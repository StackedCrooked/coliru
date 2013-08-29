#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <condition_variable>

using namespace std;

struct master;
struct worker
{
    worker(int id) : id(id) {}

    void run(master& m) const;

    int id;
};

struct master
{
    mutable mutex mx;
    mutable condition_variable cv;

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
            signal();
        }
    }

  private:
    void signal()
    {
        lock_guard<mutex> lk(mx);

        std::cout << "signaling one\n";
        cv.notify_one();
    }

    vector<worker> workers;
    vector<thread> threads;
};

void worker::run(master& m) const
{
    unique_lock<mutex> lk(m.mx);
    m.cv.wait(lk);
    cout << "signaled: " << id << "\n";
}

int main()
{
    master instance;
    instance.drive();
}
