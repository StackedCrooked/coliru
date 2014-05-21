#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>


// counters
std::atomic<uint64_t> n[100];


// counter indices
enum { i = 6, j = 7, k = 8 };


int main()
{    
    std::thread([]{ while (++n[i]); }).detach();
    std::thread([]{ while (++n[j]); }).detach();
    std::thread([]{ while (++n[k]); }).detach();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << n[i] << '\n'
              << n[j] << '\n'
              << n[k] << '\n';
}
