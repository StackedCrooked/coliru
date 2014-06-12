#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>

std::mutex m;
static int thread_count;

auto bar = [&] {
    std::lock_guard<std::mutex> lock(m);
    std::cout << "Thread #" << ++thread_count << std::endl;
};

int main()
{
    std::vector<std::thread> threads;
    std::generate_n(std::back_inserter(threads), 5,
                    [](){ return std::thread(bar); });
    
    for (auto& th : threads)
        th.join();
}