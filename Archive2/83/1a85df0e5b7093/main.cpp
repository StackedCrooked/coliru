#include <iostream>
#include <limits>
int main()
{
    double max = std::numeric_limits<double>::max();
    double inf = std::numeric_limits<double>::infinity();
 
    if(inf > max)
        std::cout << inf << " is greater than " << max << '\n';
}
