#include <chrono>
#include <iostream>


int main()
{
    using namespace std::chrono_literals;
    std::cout << (1s + 2ms + 3us + 4ns).count() << "ns\n";
}
