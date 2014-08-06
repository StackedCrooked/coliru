#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
 
int main() {
    std::vector<int> v1 {1, 2, 5, 5, 5, 9};
    std::vector<int> v2 {2, 5, 7};
    std::vector<int> diff;
 
    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), 
                        std::inserter(diff, diff.begin()));
 
    for (auto i : v1) std::cout << i << ' ';
    std::cout << "minus ";
    for (auto i : v2) std::cout << i << ' ';
    std::cout << "is: ";
 
    for (auto i : diff) std::cout << i << ' ';
    std::cout << '\n';
}