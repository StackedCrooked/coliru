#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
    const char *str  = "hello world";
    const char *oops = "zzzzzzzzzzz";

    std::copy_n(str, 20, std::ostream_iterator<char>(std::cout));

    std::istringstream iss("hello world");

    std::copy_n(std::istream_iterator<char>(iss),
                20,
                std::ostream_iterator<char>(std::cout));
}