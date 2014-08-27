#include <set>
#include <iterator>
#include <algorithm>
#include <iostream>

int main() {
    int a[] = {1, 2, 3, 1, 2, 3, 4};
    
    std::set<int> s(std::begin(a), std::end(a));
    std::copy(s.begin(), s.end(), a);
    
    std::copy(a, a+s.size(), std::ostream_iterator<int>(std::cout, "\t"));
    std::cout << std::endl;
    
    return 0;
}