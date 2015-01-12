#include <iostream>
#include <algorithm>

int main() {
    const std::vector<int> v {1, 2, 3, 4, 5, 6};
    int c = std::count(v.cbegin(), v.cend(), 2);
    std::cout << c << std::endl;
    return 0;
}