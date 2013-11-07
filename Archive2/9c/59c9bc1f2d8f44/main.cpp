#include <limits>
#include <cstddef>
#include <iostream>
int main()
{
    std::cout << "short: " << std::dec << std::numeric_limits<short>::max()
              << " or " << std::hex << std::showbase << std::numeric_limits<short>::max() << '\n'
              << "int: " << std::dec << std::numeric_limits<int>::max()
              << " or " << std::hex << std::numeric_limits<int>::max() << '\n' << std::dec
              << "streamsize: " << std::dec << std::numeric_limits<std::streamsize>::max()
              << " or " << std::hex << std::numeric_limits<std::streamsize>::max() << '\n'
              << "size_t: " << std::dec << std::numeric_limits<std::size_t>::max()
              << " or " << std::hex << std::numeric_limits<std::size_t>::max() << '\n'
              << "float: " << std::numeric_limits<float>::max();
              /*<< " or " << std::hexfloat << std::numeric_limits<float>::max() << '\n'
              << "double: " << std::defaultfloat << std::numeric_limits<double>::max()
              << " or " << std::hexfloat << std::numeric_limits<double>::max() << '\n';*/
}