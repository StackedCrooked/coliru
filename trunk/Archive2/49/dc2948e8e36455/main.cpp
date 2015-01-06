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
//enum classes

enum class led  { red=0, green=1, blue=2 };
enum class mood { blue=0, funny=1, excited=2};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    led myLed;
    mood myMood;
    
    //try out the these:
    myLed = blue;
    myMood = blue;
    
    myLed = funny;
    myMood = green;
}
