#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <iostream>

struct MyClass
{
    mutable boost::condition_variable cv;
    mutable boost::mutex mx;
    bool interrupt_requested; // protect by mx

    MyClass() : interrupt_requested(false) {}

    boost::thread timeoutThread;
    boost::thread workerThread;

    void TimeoutThread() {
        boost::this_thread::sleep_for(boost::chrono::seconds(2));

        boost::unique_lock<boost::mutex> lk(mx);
        interrupt_requested = true;
        cv.notify_all();
    }

    void WorkerThread() {
        
        while(true)
        {
            {
                boost::unique_lock<boost::mutex> lk(mx);
                if (cv.wait_for(lk, boost::chrono::milliseconds(100), boost::bind(&MyClass::interrupt_requested, this)))
                    return;
            }
            std::cout << "." << std::flush;
            //Do stuff
        }
    }

    void run()
    {
        timeoutThread = boost::thread(boost::bind(&MyClass::TimeoutThread, this));
        workerThread  = boost::thread(boost::bind(&MyClass::WorkerThread, this));
        workerThread.join();
        timeoutThread.join();
    }
};

int main()
{
    MyClass x;
    x.run();
}
