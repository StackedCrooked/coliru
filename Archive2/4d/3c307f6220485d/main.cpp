#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

bool is_even(int a) {
    return (a % 2 == 0);
}
 
int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    std::vector<int> other;
    std::remove_copy_if(begin(v), end(v), std::back_inserter(other), is_even);
    for (auto el : v) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
    for (auto el : other) {
        std::cout << el << ' ';
    }
}