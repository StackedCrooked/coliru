#include <iostream>

int main()
{
    union {
        double dbl;
        uint64_t uint;
    } val;
    val.uint = 0x401c000000000000;
    std::cout << val.dbl << std::endl;
}
