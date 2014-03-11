#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <condition_variable>
 
namespace demo
{
    namespace chrono = std::chrono;

    using our_clock = chrono::system_clock;

    struct Worker
    {
        mutable std::mutex _mx;

        // shared, protected by _mx:
        our_clock::time_point _deadline; 
        mutable std::condition_variable _cv;

        Worker(our_clock::time_point deadline) : _deadline(deadline) {}

        void operator()() const {
            std::unique_lock<std::mutex> lk(_mx);
            _cv.wait_until(lk, _deadline, [this] 
                    { 
                        std::cout << "worker: Signaled\n";
                        auto now = our_clock::now();
                        if (now >= _deadline)
                            return true;
                        std::cout << "worker: Still waiting " << chrono::duration_cast<chrono::milliseconds>(_deadline - now).count() << "ms...\n"; 
                        return false;
                    });
            std::cout << "worker: Done\n";
        }
    };
}

int main()
{
    using namespace demo;

    Worker worker(our_clock::now() + chrono::seconds(2));
    auto th = std::thread(std::cref(worker));

    // after 2 seconds, update the timepoint
    std::this_thread::sleep_for(chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lk(worker._mx);
        std::cout << "Updating shared delay value..." << "\n";

        worker._deadline = our_clock::now() + chrono::seconds(1);
        worker._cv.notify_all();
    }

    th.join();
}
