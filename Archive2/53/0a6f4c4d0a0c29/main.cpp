#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>

namespace demo
{
    namespace chrono = std::chrono;

    using our_clock = chrono::system_clock;
    using shared_delay = std::atomic<our_clock::duration>;

    void worker(our_clock::time_point const start, shared_delay const& delay)
    {
        for (our_clock::time_point deadline; our_clock::now() < (deadline = start + delay.load());)
        {
            std::cout << "worker: Sleeping for " << chrono::duration_cast<chrono::milliseconds>(deadline - our_clock::now()).count() << "ms...\n";
            std::this_thread::sleep_until(deadline);
        }

        std::cout << "worker: Done\n";
    }
}

int main()
{
    using namespace demo;

    shared_delay delay(chrono::seconds(10));
    auto th = std::thread(worker, our_clock::now(), std::cref(delay));

    // after 2 seconds, update the timepoint
    //std::this_thread::sleep_for(chrono::seconds(1));
    std::cout << "Updating shared delay value..." << "\n";
    delay.store(chrono::seconds(10));

    th.join();
}