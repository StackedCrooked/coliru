#include <iostream>
#include <string>
#include <vector>
#include <thread>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}



class Basic 
{
    public:
    Basic();
    ~Basic();
    private:
    
};


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}

Basic::Basic()
{
}

Basic::~Basic()
{
    
}