#include <set>
#include <iterator>
#include <algorithm>
#include <iostream>

int main() {
    int a[] = {1, 2, 3, 1, 2, 3, 4};

    std::sort(std::begin(a), std::end(a));
    int * last = std::unique(std::begin(a), std::end(a));
    int dedup_size = last - a;
    
    std::copy(a, a+dedup_size, std::ostream_iterator<int>(std::cout, "\t"));
    std::cout << std::endl;
    
    return 0;
}