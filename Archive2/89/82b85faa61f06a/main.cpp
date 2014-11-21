#include <iostream>
#include <string>
#include <vector>
#include <boost/functional/hash.hpp>

using namespace std;

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
    boost::hash<std::string> string_hash;

    cout<<(int)string_hash("addwfecvzbHash me")<<endl;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
