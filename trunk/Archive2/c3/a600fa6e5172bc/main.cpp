#include <iostream>
#include <chrono>
 
int main()
{
    typedef std::chrono::duration<int, std::ratio<1, 100000000>> shakes;
    typedef std::chrono::duration<int, std::centi> jiffies;
    typedef std::chrono::duration<float, std::ratio<12096,10000>> microfortnights;
    typedef std::chrono::duration<float, std::ratio<3155,1000>> nanocenturies;
 
    std::chrono::seconds sec(1);
 
    std::cout << "1 second is:\n";
 
    std::cout << std::chrono::duration_cast<shakes>(sec).count()
              << " shakes\n";
    std::cout << std::chrono::duration_cast<jiffies>(sec).count()
              << " jiffies\n";
    std::cout << microfortnights(sec).count() << " microfortnights\n";
    std::cout << nanocenturies(sec).count() << " nanocenturies\n";
}