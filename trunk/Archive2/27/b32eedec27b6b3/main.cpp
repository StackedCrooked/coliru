#include <iostream>

#define ASSERT(expr, ...) print(#expr, expr, ""__VA_ARGS__)

void print(const char str[], bool val, const char descr[])
{
    std::cout << (val ? "passed: " : "failed: ");
    std::cout << str;

    if (descr[0] != '\0') {
        std::cout << " (" << descr << ')';
    }

    std::cout << std::endl;
}

int
main(void)
{
    ASSERT(true && true && true);
    ASSERT(true && true && true, "is always true");
    ASSERT(true && false);
    ASSERT(true && false, "is actually false");
    return 0;
}
