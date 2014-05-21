#include <iostream>
#include <vector>

template<class T>
inline std::ostream& operator <<(std::ostream& ss, std::vector<T> const& vec)
{
    auto it(begin(vec));
    if (it != end(vec))
        ss << *(it++);
    for (; it != end(vec); ++it)
        ss << " " << *it;
    return ss;
}

namespace foo {
    inline std::ostream& operator <<(std::ostream& ss, const std::vector<double> &v)
    {
        return ss;
    }
    
    void bar() {
        std::cout << std::vector<int>{};   
    }
}

int main() {
    foo::bar();
}