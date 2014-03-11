#include <iostream>
#include <algorithm>

int main() {
    std::vector<int> list = { 3, 2, 1 };
    std::sort(list.begin(),list.end());
    for (const auto e : list) {
        std::cout << e << std::endl;    
    }
}