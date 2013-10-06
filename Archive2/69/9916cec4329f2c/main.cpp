#include <algorithm>
#include <iostream>
#include <iterator>

int main() {
    int a[] = {-5, -5, -2, -9, -9, -3, 1, -2};
    std::cout << *std::min_element(std::begin(a), std::end(a), [](int i1, int i2) {return i1 > 0 && (i2 <= 0 || i1 < i2);});
}