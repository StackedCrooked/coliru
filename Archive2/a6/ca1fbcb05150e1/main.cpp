#include <string>
#include <complex>
#include <chrono>
#include <iostream>
 
int main()
{
    using namespace std::literals;

    std::cout << "Hello, world"s.size() << '\n' // string
              << 1.2 + 2.1i << '\n'; // complex number

    auto tp = 120ms + 1s; // 1 second and 120 milliseconds
    std::cout << "1s + 120ms = " << tp.count() << "ms\n";
}
