#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <iostream>

using namespace boost;
using namespace boost::posix_time;

#define TRACE(msg) do { \
    std::cout << __FUNCTION__ << ':' << __LINE__ << " " << to_simple_string(posix_time::microsec_clock::local_time()) << " " << (msg) << "\n"; } while(0)

struct workers
{
    mutex mx;
    condition_variable cv;
    bool canceled;

    workers() : canceled(false) {}

    void thread1()
    {
        TRACE("start");
        this_thread::sleep_for(chrono::seconds(2));

        {
            unique_lock<mutex> lk(mx);
            TRACE("signaling cancel");
            canceled = true;
            cv.notify_all();
        }

        this_thread::sleep_for(chrono::seconds(2));
        TRACE("done");
    }

    void thread2()
    {
        TRACE("start");

        for(;;)
        {
            // do some work
            unique_lock<mutex> lk(mx);
            if (cv.wait_for(lk, chrono::milliseconds(10), boost::bind(&workers::canceled, this)))
                break;
        }

        TRACE("done");
    }
};

int main()
{
    workers demo;
    thread t1(&workers::thread1, ref(demo));
    thread t2(&workers::thread2, ref(demo));

    t1.join();
    t2.join();
}
