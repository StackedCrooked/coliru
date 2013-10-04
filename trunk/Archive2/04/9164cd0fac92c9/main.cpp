#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct Number
{
    int i;
    std::string s;
};

int main()
{   
    std::vector<Number> vec = {{2, "two"}, {8, "eight"}};

    std::sort(begin(vec), end(vec), [](Number const& L, Number const& R){
        return L.i < R.i;
    });
    std::cout << vec.front().i << ", " << vec.back().i << "\n";  // 2, 8

    std::sort(begin(vec), end(vec), [](Number const& L, Number const& R){
        return L.s < R.s;
    });
    std::cout << vec.front().s << ", " << vec.back().s << "\n";  // eight, two
}
