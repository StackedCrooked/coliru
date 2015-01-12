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

class Blah
{
private:
    class InnerClass
    {
    public:
        
        int A;
    };
    
    InnerClass Inner;
};

Blah Blah;

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    Blah.Inner.A = 1;
}
