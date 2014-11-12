#include <iostream>
#include <vector>

inline std::ostream& operator <<(std::ostream& ss, std::vector<double> const& vec)
{
    auto it(begin(vec));
    if (it != end(vec))
        ss << *(it++);
    for (; it != end(vec); ++it)
        ss << " " << *it;
    return ss;
}

namespace foo {
    template<class T>
    inline std::ostream& operator <<(std::ostream& ss, const std::vector<T> &v)
    {
        return ss;
    }
    
    void bar() {
        using ::operator<<;
        std::cout << std::vector<int>{};   
    }
}

int main() {
    foo::bar();
}