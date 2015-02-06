#include <iostream>
#include <iomanip>

int main()
{
    const double v = 12.34567 ;

    std::cout << std::fixed << std::setprecision(3)
              << std::setfill('0') << std::setw(10) << v << '\n' // 000012.346
              << v << '\n' // 12.346 // default width; setw(8) is no longer in efffect
              << std::setw(12) << v << '\n' // 00000012.346 // setfill('0') is still in effect
              << std::setw(5) << v << '\n' ; // 12.346 // width of 5 is too small; setw(5) is ignored
}
