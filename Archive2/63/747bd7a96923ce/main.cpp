#include <iostream>
#include <vector>

namespace foo
{
    template<class T>
    inline std::ostream& operator<<(std::ostream& ss, std::vector<T> const& vec)
    {
        auto it(begin(vec));
        if (it != end(vec))
            ss << *(it++);
        for (; it != end(vec); ++it)
            ss << " " << *it;
        return ss;
    }
}

void bar(const std::vector<int> &v) {
    std::cout << v;
}

int main() {
    bar({});  
}