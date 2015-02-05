#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
int main()
{
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<std::string> ans;
    std::transform(v1.begin(),v1.end(),ans.begin(),[](int i)->std::string {return((i%2) ? "odd " : "even ");});
    // Use one of stl algorithms to create one liner returning string stating if values are even or odd
    // than print this string on screen
    std::string s;
    std::for_each(ans.begin(),ans.end(),[&s](std::string text){s += text;});
    
    assert("odd even odd even odd even odd even odd even " == s);
}
