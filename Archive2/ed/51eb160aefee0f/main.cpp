#include <iostream>
#include <iomanip>

int main()
{
    std::cout << fixed << 2.7 << '\n' ; // *** error
    std::cout << setprecisin(2) << 2.7 << '\n' ; // *** error
}
