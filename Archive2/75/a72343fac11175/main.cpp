#include <iostream>
#include <string>
#include <sstream>


int main()
{std::string test = ((std::ostringstream&)
         (std::ostringstream("") << "This is a test: " << 50.1 << "abc")
         ).str();
std::cout << test;
}
