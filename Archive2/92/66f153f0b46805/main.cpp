#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
 
struct less_than_7 : std::unary_function<int, bool>
{
    bool operator()(int i) const { return i < 7; }
};
 
int main()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);
 
    std::cout << std::count_if(v.begin(), v.end(), std::not1(less_than_7()));
 
    /* C++11 solution:
        // Cast to std::function<bool (int)> somehow - even with a lambda
        std::cout << std::count_if(v.begin(), v.end(),
            std::not1(std::function<bool (int)>([](int i){ return i < 7; }))
        );
    */
}