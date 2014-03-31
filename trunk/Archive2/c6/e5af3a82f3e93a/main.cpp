#include <thread>
#include <condition_variable>
#include <iostream>

struct MyClass
{
    mutable std::condition_variable cv;
    mutable std::mutex mx;
    bool interrupt_requested; // protect by mx

    MyClass() : interrupt_requested(false) {}

    std::thread timeoutThread;
    std::thread workerThread;

    void TimeoutThread() {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::unique_lock<std::mutex> lk(mx);
        interrupt_requested = true;
        cv.notify_all();
    }

    void WorkerThread() {
        
        while(true)
        {
            {
                std::unique_lock<std::mutex> lk(mx);
                if (cv.wait_for(lk, std::chrono::milliseconds(100), std::bind(&MyClass::interrupt_requested, this)))
                    return;
            }
            std::cout << "." << std::flush;
            //Do stuff
        }
    }

    void run()
    {
        timeoutThread = std::thread(std::bind(&MyClass::TimeoutThread, this));
        workerThread  = std::thread(std::bind(&MyClass::WorkerThread, this));
        workerThread.join();
        timeoutThread.join();
    }
};

int main()
{
    MyClass x;
    x.run();
}
