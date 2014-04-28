#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

int main()
{
    std::istringstream iss("1 2 hello");
    std::copy_n(std::istream_iterator<int>(iss), 2, std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\nfailed? " << std::boolalpha << iss.fail() << "\n";
}