#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>


struct Blocker
{
    Blocker(unsigned n) : n(n) {}

    void notify()
    {
        std::cout << "notify()" << std::endl;
        std::unique_lock<std::mutex> lock(m);
        if (n)
        {
            n--;
        }
        c.notify_all();
    }

    void wait()
    {
        std::cout << "Gonna wait." << std::endl;
        std::unique_lock<std::mutex> lock(m);
        std::cout << "n is " << n << " before wait." << std::endl;
        while (n)
        {
            c.wait(lock);
            std::cout << "Received notification!" << std::endl;
        }
    }

    unsigned n;
    std::mutex m;
    std::condition_variable c;
};

template<typename Callback>
void async_operation(const Callback & cb)
{
    std::thread(cb).join();
}


int main()
{
    Blocker b(1);
    async_operation([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Finished my work. Gonna notify." << std::endl;
        b.notify();
        std::cout << "Did the notify." << std::endl;
    });
    b.wait();

    std::cout << "End of program." << std::endl;
}
