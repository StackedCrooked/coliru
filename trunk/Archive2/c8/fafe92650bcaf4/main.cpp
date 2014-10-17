#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>

int main()
{
    auto vec = std::vector<int> {'h', 'e', 'l', 'l', 'o'};
    std::cout << std::hex << std::setfill('0') << std::setw(2) << std::uppercase;
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout));
}
