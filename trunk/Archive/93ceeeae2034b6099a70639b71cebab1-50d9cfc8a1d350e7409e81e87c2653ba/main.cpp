#include <vector>

#include <iostream>
int main() {
    std::vector<int> x;
    
    const std::vector<int>& r = x;
    std::cout << r.size() << '\n';

    x.push_back(17);
    std::cout << r.size() << '\n'; // oops, it changed!
}