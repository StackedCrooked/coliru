#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{std::string test = ((std::ostringstream&)
         (std::ostringstream("") << "This is a test: " << 50.1 << "abc")
         ).str();
std::cout << test;
}
