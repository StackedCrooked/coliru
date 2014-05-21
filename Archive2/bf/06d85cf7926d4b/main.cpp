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
    void bar(const std::vector<int> &v) {
        std::cout << v;
    }
}

int main() {
     foo::bar({});  
}