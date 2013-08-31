#include <iostream>
#include <array>
#include <memory>
#include <type_traits>

#include <vector>


int main() {
    std::vector<int> a, b;
    for(int i = 0; i != 100; ++i)
      a.push_back(0);
    b.resize(100);
    std::cout << a.capacity() << " , " << b.capacity() << std::endl;
}