

#include <iostream>
#include <iomanip>
#include <string>

void display_sum(int a, int b)
{
    std::cout << std::setw(10) << a  << "\n"
              << std::setw(10) << ("+" + std::to_string(b)) << "\n"
              << std::setw(10) << (a+b) <<"\n" << std::endl;
}

int main()
{
    display_sum(4555, 50);
    display_sum(500000, 12);
    display_sum(503930, 3922);
}
