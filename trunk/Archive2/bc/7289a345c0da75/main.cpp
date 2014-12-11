#include <iostream>
#include <vector>

namespace ns {

template<typename Type>
struct vector {
    std::vector<Type> items;
};

template<typename Type>
std::ostream& operator<<(std::ostream& os, vector<Type> const& v)
{
    os << "ns::vector { ";
    for(auto const& item: v.items) {
        os << item << ", ";
    }
    os << '}';
    return os;
}

struct thing {
    vector<int> data = { { 0, 1, 2 } };
};

std::ostream& operator<<(std::ostream& os, thing const& t)
{
    os << "ns::thing { ";
    os << t.data;
    os << " }";
    return os;
}

} // ns

int main()
{
    ns::vector<ns::thing> v;
    v.items.resize(2);
    std::cout << v << '\n';
}