#include <boost/variant.hpp>
#include <boost/array.hpp>
#include <bitset>
#include <iostream>

template <template <typename, size_t> class T, typename V, size_t N>
    void foo(T<V, N> const& something)
    {
        std::cout << __LINE__ << ": " << __PRETTY_FUNCTION__ << "\n";
    }
    
template <template <size_t> class T, size_t N>
    void foo(T<N> const& something)
    {
        std::cout << __LINE__ << ": " << __PRETTY_FUNCTION__ << "\n";
    }
    
int main()
{
    boost::array<int, 67> a;
    boost::array<double, 78> b;
    std::bitset<47> c;
    
    foo(a);
    foo(b);
    foo(c);
}