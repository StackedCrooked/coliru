#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void run(std::string& s)
{
    s = "zhopa";
}

int main()
{
    std::string s = "world";
    auto b = std::bind(&run, std::ref(s));
    b();
    

    std::cout << s << std::endl;
}
