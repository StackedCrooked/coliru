#include <string>

//# Header.hpp
namespace my_namespace
{
    std::string run();
}

//#include "Header.hpp"
std::string my_namespace::run()
{
    return "Hello World.";
}

int main() {}