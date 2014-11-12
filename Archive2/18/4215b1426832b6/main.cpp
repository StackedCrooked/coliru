#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout));
    return 0;
}
