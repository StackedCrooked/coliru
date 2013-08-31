#include <tuple>
#include <iomanip>
#include <iostream>

struct location { int x, y, z; };

bool operator<(const location& lhs, const location& rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
}

int main()
{
    location a = {0, 1, 2}, b = {0, 1, 3};

    std::cout << std::boolalpha << (a < b) << std::endl;
}
