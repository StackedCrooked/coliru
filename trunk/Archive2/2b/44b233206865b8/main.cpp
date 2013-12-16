#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

struct X
{
    std::condition_variable cv;
    std::mutex mx;
    bool isStarted;
    std::thread worker;

    X() : isStarted(false) {}

    void aMethod()
    {
        worker = std::thread(&X::Worker, this);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::cout << "signalling worker\n";
            std::unique_lock<std::mutex> lock(mx);
            isStarted = true;
            cv.notify_one();
        }

        worker.join();
        isStarted = false;
    }

    void Worker()
    {
        std::unique_lock<std::mutex> lock(mx);
        std::cout << "worker ready\n";
        cv.wait(lock, [this] { return isStarted; });
        std::cout << "worker started\n";

        std::cout << "worker done\n";
    }
};

int main()
{
    X o;
    o.aMethod();
}
