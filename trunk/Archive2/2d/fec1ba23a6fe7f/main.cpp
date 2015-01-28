#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>

template<class T>
class X
{
    T data;
    
public:    
    /* implicit */ X(T const& t) : data(t) {}
    /* implicit */ operator auto() const { return data; }
};

BOOST_AUTO_TEST_CASE(Bla)
{
    auto v = std::vector<X<int>> { 0, 1, 2, 3 };    
    auto w = std::vector<X<int>> { 0, 1, 2, 3 };    
    for (auto const& e : v) std::cout << e << ", ";
    
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(v), end(v), begin(w), end(w));
}


