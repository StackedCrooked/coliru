#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
 
struct same : std::binary_function<bool, int, int>
{
    bool operator()(int a, int b) const { return a == b; }
};
 
int main()
{
    std::vector<int> v1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::vector<bool> v3(v1.size());
 
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::not2(same()));
 
    std::cout << std::boolalpha;
    for (std::size_t i = 0; i < v1.size(); ++i)
        std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';
}