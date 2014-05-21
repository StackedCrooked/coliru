#include <boost/format.hpp>
#include <string>

template <typename... Args>
std::string format(const char* formatString, Args&&... args)
{
    using for_each_variadic = int[];
    boost::format f(formatString);
    for_each_variadic{(f % std::forward<Args>(args),0)...,0};
    return f.str();
}

template <typename... Args>
std::string format(const std::string& formatString, Args&&... args)
{return format(formatString.c_str(),std::forward<Args>(args)...);}

#include <iostream>
int main() {
    std::cout << format("%s_%06d.dat", "myfile", 18); // myfile_000018.dat
}