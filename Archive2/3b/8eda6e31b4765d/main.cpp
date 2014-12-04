#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
 
int main()
{
    std::vector<char> v1 {'a', 'b', 'c', 'd'};
    std::vector<char> v2 {'a', 'b', 'c', 'd'};
 
    std::srand(std::time(0));
    while (!std::lexicographical_compare(v1.begin(), v1.end(),
                                         v2.begin(), v2.end())) {
        for (auto c : v1) std::cout << c << ' ';
        std::cout << ">= ";
        for (auto c : v2) std::cout << c << ' ';
        std::cout << '\n';
 
        std::random_shuffle(v1.begin(), v1.end());
        std::random_shuffle(v2.begin(), v2.end());
    }
 
    for (auto c : v1) std::cout << c << ' ';
    std::cout << "< ";
    for (auto c : v2) std::cout << c << ' ';
    std::cout << '\n';
}