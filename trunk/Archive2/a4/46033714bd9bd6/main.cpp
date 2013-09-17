#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
 
struct LessThan7 : std::unary_function<int, bool>
{
    bool operator()(int i) const { return i < 7; }
};
 
int main()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
 
    std::cout << std::count_if(v.begin(), v.end(), std::not1(LessThan7())) << "\n";
 
    //same as above, but use a lambda function
    std::function<int(int)> less_than_9 = [](int x){ return x < 8; };
    std::cout << std::count_if(v.begin(), v.end(), std::not1(less_than_9)) << "\n";
}