#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

struct foo
{
    void updateTimer()
    {
        while(running_) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Hello" << std::endl;
        }
    }
    
    std::atomic_bool running_{true};
    std::thread t{&foo::updateTimer, this};
    ~foo()
    {
        running_ = false;
        t.join();
        std::cout << "Thread stopped\n";
    }
};

int main()
{
    {
        foo f;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    std::cout << "End\n";
}
