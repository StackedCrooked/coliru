#include <iostream>
#include <string>
#include <vector>
using namespace std;

//This does not work
//typedef string * string2d[2];
//typedef string *(&string2d)[2];

typedef string (&string2d)[23][2];

string2d flowFile() {
    static string flow[23][2];
   return flow;
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
