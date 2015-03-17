#include <iostream>
#include <chrono>
 
int main()
{
    using shakes = std::chrono::duration<int, std::ratio<1, 100000000>>;
    using jiffies = std::chrono::duration<int, std::centi>;
    using microfortnights = std::chrono::duration<float, std::ratio<12096,10000>>;
    using nanocenturies = std::chrono::duration<float, std::ratio<3155,1000>>;
 
    std::chrono::seconds sec(1);
 
    std::cout << "1 second is:\n";
 
    std::cout << std::chrono::duration_cast<shakes>(sec).count()
              << " shakes\n";
    std::cout << std::chrono::duration_cast<jiffies>(sec).count()
              << " jiffies\n";
    std::cout << microfortnights(sec).count() << " microfortnights\n";
    std::cout << nanocenturies(sec).count() << " nanocenturies\n";
}