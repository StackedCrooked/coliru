#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>

#include <cstdlib>

struct A
{
    
    A() : i(std::numeric_limits< double >::quiet_NaN()) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    A(double ii) : i(ii) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    A(A const & a) : i(a.i) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    A(A && a) : i(std::move(a.i)) { std::cout << __PRETTY_FUNCTION__ << "\n"; a.i = std::numeric_limits< double >::quiet_NaN(); }
    A & operator = (A const & a) { std::cout << __PRETTY_FUNCTION__ << "\n"; i = a.i; return *this; }
    A & operator = (A && a) { std::cout << __PRETTY_FUNCTION__ << "\n"; i = std::move(a.i); a.i = std::numeric_limits< double >::quiet_NaN(); return *this; }
    bool operator < (A const & a) const { std::cout << __PRETTY_FUNCTION__ << "\n"; return (i < a.i); }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
    bool operator == (A const & a) const { std::cout << __PRETTY_FUNCTION__ << "\n"; return (i == a.i); }
#pragma clang diagnostic pop
    
    friend
    std::ostream &
    operator << (std::ostream & o, A const & a)
    {
        return o << a.i;
    }
    
private :

    double i;
    
};

int
main()
{
    std::vector< A > v{1.0, 1.0, 2.0, 2.0, 2.0, 3.0, 4.0, 4.0, 5.0, 6.0, 6.0, 7.0};
    std::cout << "v constructed\n\n\n\n";
    std::sort(v.begin(), v.end());
	auto const end = std::unique(v.begin(),v.end());
    std::copy(v.begin(), end, std::ostream_iterator< A >(std::cout, " "));
	std::cout << std::endl;
    return EXIT_SUCCESS;
}
