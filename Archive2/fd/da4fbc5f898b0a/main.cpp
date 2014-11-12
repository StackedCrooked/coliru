#include <thread>
#include <iostream>
#include <atomic>


std::atomic<uint64_t> n[50];


int main()
{
    std::thread([]{ for(;;) n[22]++; }).detach();
    std::thread([]{ for(;;) n[23]++; }).detach();
    std::thread([]{ for(;;) n[33]++; }).detach();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << n[22] << '\n'
              << n[23] << '\n'
              << n[33] << '\n';
}
