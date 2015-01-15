#include <iostream>
#include <string>
#include <vector>

void f() {
    using namespace 
    std::string s = [](){ return "mola"; }
    cout << s << endl;
}


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
}
