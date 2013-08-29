#include <algorithm>
#include <iterator>
#include <ios>
#include <iostream>
#include <set>
#include <string>

int main()
{
    auto const ss = std::set<std::string> { "foo", "bar", "test" };
    std::cout << std::boolalpha << std::is_sorted(begin(ss), end(ss)) << "\n";
    std::cout << std::boolalpha << (std::adjacent_find(begin(ss), end(ss)) == end(ss)) << "\n";
    std::copy(begin(ss), end(ss), std::ostream_iterator<std::string>(std::cout, "\n"));
}