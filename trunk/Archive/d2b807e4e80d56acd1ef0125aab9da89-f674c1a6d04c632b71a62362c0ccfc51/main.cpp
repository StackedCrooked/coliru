#include <iostream>
#include <string>
#include <vector>

#include <memory>

struct x {
    std::unique_ptr<int> m;
    
    x(): m(new int(3)) {};
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
    const x tx;
    //tx.m = std::unique_ptr<int>(new int(3));
    *tx.m = 4;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    std::cout <<  *tx.m << std::endl;
}
