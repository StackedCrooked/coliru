
#include <iostream>
#include <iomanip>

#define X (200075.00000000000 / 1000.0000000000000)
#define Y (100075.00000000000 / 1000.0000000000000)

int main()
{
    std::cout << X << std::endl;
    std::cout << Y << std::endl;
    
    std::cout << std::setprecision(3) << X << std::endl;
    std::cout << std::setprecision(3) << Y << std::endl;
}
