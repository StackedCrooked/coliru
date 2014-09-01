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
    int mynum;
    std::vector<std::string> words = {
        "Hi", "from", "Ashley", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    mynum = 10/0;
    mynum = mynum * mynum;
    std::cout << mynum << std::endl;

}
