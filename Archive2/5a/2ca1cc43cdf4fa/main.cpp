#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
    std::string test = ((std::ostringstream&)
         (std::ostringstream("") << "This is a test: " << 50.1 << "abc")
         ).str();
    std::cout << test << std::endl;
    return 0;
}