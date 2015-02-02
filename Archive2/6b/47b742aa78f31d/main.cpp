#include <boost/range/adaptors.hpp>
#include <iostream>

struct TrivialTrafo {
    typedef int result_type;
    template <typename T>
        int operator () (T const&) const { return 1; }
};

int main()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back (i);

    for (auto&& x : v | boost::adaptors::transformed (TrivialTrafo ()) 
        | boost::adaptors::strided (2))
    {
        std::cout << x << " ";
    }
}
