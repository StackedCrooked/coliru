#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>

    template<typename T>
    bool my_equal(const T& a, const T& b) {
        return a == b;
    }

    template<typename T>
    bool my_equal(const char* a, const char* b) {
        return !strcmp(a, b);
    }
    
int main() {
    std::cout << my_equal(1, 2) << std::endl;
    std::cout << my_equal(1, 1) << std::endl;
    std::cout << my_equal("abc", "def") << std::endl;
    char* a = new char[]({'a', 'b', 'c', 0});
    std::cout << my_equal("abc", a) << std::endl;
    
}
