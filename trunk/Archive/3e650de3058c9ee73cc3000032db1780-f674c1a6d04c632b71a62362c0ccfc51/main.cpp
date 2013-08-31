#include <unordered_map>
#include <iostream>

int main() {
    typedef std::unordered_map< int, int > map_t;
    map_t m1, m2;
    
    auto it = m1.begin();
    std::cout << (int)(it == m1.end()) << std::endl;
    std::cout << (int)(it == m2.end()) << std::endl;
    return 0;
}