#include <iostream>
#include <stdexcept>
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


namespace company {
namespace std {

template<typename T>
class vector : public ::std::vector<T>
{
    using base = ::std::vector<T>;

public:
    using ::std::vector<T>::vector;

    using typename base::size_type;
    using typename base::reference;
    using typename base::const_reference;

    const_reference operator[](size_type n) const { return base::at(n); }
    reference operator[](size_type n) { return base::at(n); }
};

} // namespace


void test(const std::vector<int> vec)
{
    vec[vec.size()]; // out of bounds
}

}

int main()
{

    namespace std = company::std;


    std::vector<int> vec;
    company::test(vec);
}
