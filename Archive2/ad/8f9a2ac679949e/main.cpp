#include <boost/thread.hpp>
#include <iostream>

struct MyClass
{
    boost::thread timeoutThread;
    boost::thread workerThread;

    void TimeoutThread() {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(15));
        workerThread.interrupt();
    }

    void WorkerThread() {
        while(!boost::this_thread::interruption_requested())
        {
            //Do stuff
            std::cout << "." << std::flush;
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
