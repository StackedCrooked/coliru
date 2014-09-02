#include <iostream>
#include <chrono>
#include <cstdint>
#include <thread>

typedef std::chrono::duration<std::int64_t, std::nano> ns_t;

void foo(void)
{
    std::cout << "Jesus, take the wheel" << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(2));
}

int main()
{
    auto t1 = std::chrono::steady_clock::now();
    std::cout << "Jesus, take the wheel ";
    auto t2 = std::chrono::steady_clock::now();

    ns_t ns = std::chrono::duration_cast<ns_t>(t2 - t1);
    std::cout << ns.count() << " ns" << std::endl;

    return 0;
}
