#include <sstream>
#include <iostream>
#include <string>

long long strtoull16(const char* str, char** err, int dummy)
{
    long long result = 0;
    std::istringstream is(str);
    is >> std::hex >> result;
    return result;
}

int main()
{
    const char* str = "0x0A";
    char* dummy;
    long long v = strtoull16(str, &dummy, 16);
    std::cout << v << std::endl;
}
