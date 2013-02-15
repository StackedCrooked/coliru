#include <iostream>
#include <regex>
#include <stdexcept>

int main() {
    try
    {
        std::regex("\\d");
    }
    catch (const std::exception & e)
    {
        std::cout << e.what();
    }
}