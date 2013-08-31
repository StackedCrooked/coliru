#include <vector>
#include <iostream>


int main() {
    std::vector<int> v;
    v.reserve(8);
    std::cout << v.capacity() << std::endl;
    
    for(int i = 0; i < 8; ++i) {
        v.push_back(i);
    }
    std::cout << v.capacity() << std::endl;
    
    v.resize(4);
    std::cout << v.capacity() << std::endl;
    
    v.resize(0);
    std::cout << v.capacity() << std::endl;
}