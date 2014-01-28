#include <iostream>
#include <string>
#include <set>

int main()
{
    std::set<long> s { 1, 2, 3 };
    
    if (s.find(3) == s.end()) {
        std::cout << "OK\n";
    }
    else {
        std::cout << "ERROR\n";
    }
}
