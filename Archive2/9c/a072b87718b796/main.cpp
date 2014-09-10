#include <iostream>
#include <iomanip>
#include <ctime>

int main()
{
    std::time_t t = std::time(nullptr);
    std::cout << std::put_time(std::localtime(&t), "%a %b %d %I:%M:%S %p") << '\n';
}