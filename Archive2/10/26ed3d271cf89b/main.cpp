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
namespace N {
    struct T {};
    std::ostream& operator<<(std::ostream&,T const&);
    void f() {
        std::vector<T> v;
        std::cout << v;
    }
}

int main()
{
    N::f();
}
