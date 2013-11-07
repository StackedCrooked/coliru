#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<int> testvec;
    testvec.resize(5);
    testvec[0]=12;
    testvec[3]=15;
    for(auto it=testvec.begin();it!=testvec.end();++it)
        std::cout << *it << '\n';
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
