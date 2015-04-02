#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>

int main()
{
    std::cout << std::fixed << (time(0) * 1e9) << '\n';
    std::cout << std::numeric_limits<uint64_t>::max() << '\n';
    std::cout << std::numeric_limits<int64_t>::max() << '\n';
}
