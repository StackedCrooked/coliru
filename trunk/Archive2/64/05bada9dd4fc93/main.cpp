#include <vector>
#include <algorithm>
#include <iostream>
 
struct Sum {
    Sum() { sum = 0; }
    void operator()(int n) { sum += n; }
 
    int sum;
};
 
int main()
{
    std::vector<int> nums{3, 4, 2, 9, 15, 267};
 
    std::cout << "до: ";
    for (auto n : nums) {
        std::cout << n << " ";
    }
    std::cout << '\n';
 
    std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());
 
    std::cout << "после:  ";
    for (auto n : nums) {
        std::cout << n << " ";
    }
    std::cout << '\n';
    std::cout << "сумма: " << s.sum << '\n';
}