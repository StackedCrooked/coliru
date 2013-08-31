#include <iostream>
#include <thread>
#include <vector>

struct S {};
thread_local S global_s;

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread([](){ std::cout << &global_s << '\n'; }));
    for (auto& t: threads) t.join();
}
