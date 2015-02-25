#include <iostream>
#include <string>
#include <vector>

static constexpr size_t maxSize = 10;
template<size_t N>
std::string createFixedString(char const(& fstring)[N]) {
    static_assert(N < maxSize, "Fixed length string too long");
    return std::string(fstring);
}

int main()
{
    std::cout << createFixedString("foo") << std::endl;
}
