#include <thread>
#include <condition_variable>
#include <iostream>

using namespace std;

struct workers
{
    mutex mx;
    condition_variable cv;
    bool canceled;

    workers() : canceled(false) {}

    void thread1()
    {
        cout << __PRETTY_FUNCTION__ << " start\n";
        this_thread::sleep_for(chrono::seconds(2));

        {
            unique_lock<mutex> lk(mx);
            cout << __PRETTY_FUNCTION__ << " signaling cancel\n";
            canceled = true;
            cv.notify_all();
        }

        this_thread::sleep_for(chrono::seconds(2));
        cout << __PRETTY_FUNCTION__ << " done\n";
    }

    void thread2()
    {
        cout << __PRETTY_FUNCTION__ << " start\n";

        for(;;)
        {
            // do some work
            unique_lock<mutex> lk(mx);
            if (cv.wait_for(lk, chrono::milliseconds(10), [this] { return canceled; }))
                break;
        }

        cout << __PRETTY_FUNCTION__ << " done\n";
    }
};

int main()
{
    workers demo;
    std::thread t1(&workers::thread1, ref(demo));
    std::thread t2(&workers::thread2, ref(demo));

    t1.join();
    t2.join();
}
