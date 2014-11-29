#include <iostream>
#include <chrono>
using namespace std::chrono;
int main()
{
    using namespace std::literals::chrono_literals;
    auto day = 24h;
    auto halfhour = 0.5h;
    std::cout 
        << "one day is " << day.count() << " hours\n" 
        << "one day is " << duration_cast<milliseconds>(day).count() << " seconds\n";
}