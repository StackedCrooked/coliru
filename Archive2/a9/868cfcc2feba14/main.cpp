#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>
#include <iostream>

template <typename T>
std::string to_string(std::vector<T> const& v, const char* delim = "\n")
{
    std::ostringstream oss;
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(oss, delim));
    return oss.str();
}

int main()
{
    std::cout << to_string(std::vector<double> { 1.1,2.2,3e-12 }, ";") << "\n";
    std::cout << to_string(std::vector<int> { 42, -13 }, "\t") << "\n";
    std::cout << to_string(std::vector<std::string> { "42", "-13" }) << "\n";
}
