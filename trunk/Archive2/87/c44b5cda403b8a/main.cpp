#include <iostream>
#include <functional>

void check(const char*, ...) __attribute__((format(__printf__, 1, 2)));
void check(const char*, ...)
{
    // exists only for the purposes of catching bogus format strings
}

template<const char* fmt, typename... Ts>
void check_t(Ts... ts)
{
    // check the format string by expanding ts into the check function
    check(fmt, ts...);
}

constexpr const char f[] = "foo %s";

int main()
{
    check_t<f>(5); // fails to compile
    check(f, 5);   // fails to compile
    return 0;
}
