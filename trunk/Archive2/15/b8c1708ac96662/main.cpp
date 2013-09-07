#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    vector<string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    cout << words << std::endl;
}
