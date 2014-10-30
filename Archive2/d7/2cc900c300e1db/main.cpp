#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

std::string transformToString(int value) { return std::to_string(value); }

int main()
{
    std::vector<int> v;
    v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(3);
    
    std::vector<std::string> s;
    std::transform(v.begin(), v.end(), s.begin(), transformToString);

}
