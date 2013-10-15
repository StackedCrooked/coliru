#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct sortFunc
{
    bool operator()(const int& v1, const int& v2)
    {
        int iData1 = v1;
        int iData2 = v2;
        
        return iData1 > iData2;
    }
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::vector<int> test = { 1, 6, 3, 2, 6, 3, 6, 7, 2, 6, 11};
    std::cout << test << std::endl;
    std::sort(test.begin(), test.end(), sortFunc());
    std::cout << test << std::endl;
}


