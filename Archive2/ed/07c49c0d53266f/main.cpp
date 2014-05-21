#include <boost/format.hpp>
#include <string>

template <typename... Args>
std::string format(
        std::string formatString,
        Args&&... args)
{
    using for_each_variadic = int[];
    boost::format f(std::move(formatString));
    for_each_variadic{(f % std::forward<Args>(args),0)...,0};
    return f.str();
}

#include <iostream>
int main() {
    std::cout << format("%s_%06d.dat", "myfile", 18); // myfile_000018.dat
}