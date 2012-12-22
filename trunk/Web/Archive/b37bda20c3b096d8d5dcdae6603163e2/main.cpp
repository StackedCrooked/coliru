#include <ctime>
#include <array>

int main()
{
    unsigned n = time(0) % 10;
    std::array<int, n - n + 2> arr;
}