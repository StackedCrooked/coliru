#include <iostream>

const int log_level = 2;

#define LOG(level) if (level < log_level); std::cout

int main()
{
    LOG(1) << "1";
    LOG(2) << "2";
}
