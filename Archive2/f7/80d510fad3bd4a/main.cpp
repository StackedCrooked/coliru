#include <iostream>
#include <iomanip>
#include <limits>
#include <set>

int main()
{
    using key_type = std::pair<int, int>;
    std::set<key_type> s { {1, -1}, {1, 3}, {2, 10}, {3, 42} };
    auto it = s.upper_bound (key_type (2, std::numeric_limits<int>::min ()));
    std::cout << "(" << it->first << "; " << it->second << ")\n";
}
