#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <condition_variable>

using namespace std;

struct master;

static void run(int id, master& m);
struct master
{
    mutable mutex mx;
    mutable condition_variable cv;
    int signaled_id;

    master() : signaled_id(-1)
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
        // generate random wakeup order
        vector<int> wakeups(10);
        iota(begin(wakeups), end(wakeups), 0);
        random_shuffle(begin(wakeups), end(wakeups));

        // do wakeups
        for (int id : wakeups)
        {
            this_thread::sleep_for(chrono::milliseconds(rand()%100));
            signal(id);
        }
    }

  private:
    void signal(int id)
    {
        lock_guard<mutex> lk(mx);

        std::cout << "signaling " << id << "\n";

        signaled_id = id;
        cv.notify_all();
    }

    vector<thread> threads;
};

static void run(int id, master& m)
{
    unique_lock<mutex> lk(m.mx);
    m.cv.wait(lk, [&] { return m.signaled_id == id; });
    m.signaled_id = -1;
    cout << "signaled: " << id << "\n";
}

int main()
{
    master instance;
    instance.drive();
}
