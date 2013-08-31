#include <string>
#include <iostream>
#include <stdexcept>

std::string prettify(std::string file, int line, std::string function)
{
    return file + "(" + std::to_string(line) + "), " + function + "(...): ";
}

std::runtime_error pretty_error(std::string file, int line, std::string function, std::string message)
{
    return std::runtime_error(prettify(file, line, function) + message);
}

std::string func(void)
{
    throw pretty_error(__FILE__, __LINE__, __FUNCTION__, "throwing just because");
    return std::string();
}

int main()
{
    try
    {
        func();
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << "\n";
    }
}