#include <chrono>
#include <future>
#include <iostream>

struct pretend_to_work {
    std::chrono::duration<double> duration;
    
    void operator()() const
    {
        std::this_thread::sleep_for(duration);
    }
};

int main()
{
    constexpr auto& now = std::chrono::high_resolution_clock::now;
    auto start = now();
    
    {
        auto r = std::async(std::launch::async, pretend_to_work { std::chrono::seconds { 3 } });
        pretend_to_work { std::chrono::seconds { 4 } }();
        r.get();
    }
    
    auto total = now() - start;
    std::cout << "Took\t" << std::fixed << std::chrono::duration<double> { total }.count() << " seconds.\n";
}