#include <chrono>
#include <iostream>

int main()
{
    using namespace std::chrono;

    auto epoch = high_resolution_clock::from_time_t(0);
    // ...
    auto now   = high_resolution_clock::now();

    auto mseconds = duration_cast<milliseconds>(now - epoch).count();

    std::cout << "millis: " << mseconds;
}
