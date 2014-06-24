#include <iostream>
#include <string>
#include <vector>

using namespace std;
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class C1 {
    public:
    C1(){
        cout <<" hello" << endl;
    }
    ~C1(){
        cout <<"dtor" << endl;
    }
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GC C", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    C1 c1;
    return 0;
}
