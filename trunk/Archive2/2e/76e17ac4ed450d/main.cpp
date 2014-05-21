#include <thread>
#include <iostream>
#include <atomic>
#include <chrono>


std::atomic<uint64_t> n[10];


int main()
{
    std::thread([]{ while (++n[0]); }).detach();
    std::thread([]{ while (++n[1]); }).detach();
    std::thread([]{ while (++n[9]); }).detach();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << n[0] << std::endl;
    std::cout << n[1] << std::endl;
    std::cout << n[9] << std::endl;
}
