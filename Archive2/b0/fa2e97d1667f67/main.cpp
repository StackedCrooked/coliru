#include <iostream>
#include <string>
#include <vector>
#include <array>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct Vect { float x,y,z; };

struct Tine {
    std::array <Vect, 4> pts;
};

static bool MakeHandiPointStyle (const Tine &soft_tine,
                          const Tine &hard_tine)
{ 
    return true;
}
                          
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    Tine t {1,2,3,4};
    MakeHandiPointStyle (t, {5,6,7,8});
    std::cout << words << std::endl;
}
