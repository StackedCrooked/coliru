#include <iostream>
#include <string>
#include <vector>

using namespace std;

//  My test enum
enum mmm { 
    zero,
    one,
    two,
    three
};

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
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    mmm myEnum = mmm::three;
    cout << "\n\tmyEnum = " << myEnum << endl;
}
