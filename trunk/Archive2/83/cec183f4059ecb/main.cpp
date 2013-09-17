#include <iostream>

int main()
{
    std::ostream(std::cout.rdbuf()) << u8"hello world!" << std::endl;
}
