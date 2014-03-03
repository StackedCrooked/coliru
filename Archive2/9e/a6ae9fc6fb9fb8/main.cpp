#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::fixed << std::setfill('0') << std::internal << std::setprecision(3);

    std::cout << std::setw(7);
    std::cout << 0.0f << "\n";
    std::cout << std::setw(7);
    std::cout << 1.2f << "\n";
    std::cout << std::setw(7);
    std::cout << 12.34f << "\n";
    std::cout << std::setw(7);
    std::cout << 100.125f << "\n";
}