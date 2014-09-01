#include <iostream>

#define ASSERT(expr, ...) print(#expr, expr, \
                                #__VA_ARGS__[0] ? __VA_ARGS__ : 999)

void print(const char str[], bool val, int severity)
{
    std::cout << (val ? "passed: " : "failed: ");
    std::cout << str;
    std::cout << " (" << severity << ')';
    std::cout << std::endl;
}

int
main(void)
{
    ASSERT(true && true && true);
    ASSERT(true && true && true, 14);
    ASSERT(true && false);
    ASSERT(true && false, 48);
    return 0;
}