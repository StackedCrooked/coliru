#include <iostream>
#include <string>
#include <sstream>
#include <vector>


template<typename T>
std::string to_string(const std::vector<T>& v)
{
    std::stringstream ss;
    
    ss << '[';
    for (auto& el : v)
    {
        ss << el << ' ';
    }
    auto result = ss.str();
    if (result.size() == 1) result.push_back(']');
    else result.back() = ']';
    return result;
}


std::string operator+(const std::string& s, const std::vector<int>& v)
{
    std::stringstream ss;
    ss << "sum(" << s << ", " << to_string(v) << ")";
    return ss.str();
}


int main()
{
    std::string s = "hello";
    std::vector<int> vec = { 1, 2, 3};
    std::cout << (s + vec) << std::endl;
}//ab