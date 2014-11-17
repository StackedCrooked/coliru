#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v1 {'a','l', 'a', ' ', 'm', 'a', ' ', 'k', 'o', 't', 'a'};
    std::vector <int> v2 {'k', 'o', 't'};
    
    // Na jakiej pozycji w v1 znajduje się "łańcuch" "kot" (7)
    auto it = std::search (v1.cbegin (), v1.cend (), v2.cbegin (), v2.cend ());
    std::cerr << std::distance (v1.cbegin (), it) << std::endl;
}
