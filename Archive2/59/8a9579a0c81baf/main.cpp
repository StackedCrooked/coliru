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
    struct MyClass
    {
        std::vector<int> m_vec;
    };
    inline std::ostream& operator <<(std::ostream& ss, MyClass const& in)
    {
      using ::operator<<;
      return ss << "ClassVec: " << in.m_vec;
    }
}

int main() {
    foo::MyClass test;
    test.m_vec = {1,2,3};
    std::cout << test;
}