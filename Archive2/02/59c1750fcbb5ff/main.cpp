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
class Test{
    static void t(){
    }
};
int main()
{
    using std::cout;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    for(auto iter= words.begin(); iter != words.end(); iter++){
       cout << *iter << std::endl;
    }
    std::cout << words << std::endl;
}
