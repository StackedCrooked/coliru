#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

int main()
{
    auto st = boost::filesystem::directory_entry("main.cpp").status();
    std::cout << boost::filesystem::exists(st) << std::endl;
}
