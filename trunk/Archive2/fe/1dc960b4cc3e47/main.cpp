#include <iostream>

const int log_level = 2;

#define LOG(level) if (level < log_level); else std::cout

int main()
{
    LOG(1) << "1";
    LOG(2) << "2";
}
