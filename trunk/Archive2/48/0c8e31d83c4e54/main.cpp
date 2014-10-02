#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <iostream>

// this class is not default constructible
struct  A {
    A() = delete;
    A(int x) : _i(x) {}
private:
    friend std::ostream& operator<<(std::ostream& os, A const& a) { return os << "A[" << a._i << "]"; }
    int _i;
};

//////////////////////////////////////////////////////////////////////////////////////
// This would be too easy, no?
template <typename FusionVector, typename... Ts> FusionVector fun(Ts&&... args) {
    return boost::fusion::vector<Ts...> (std::forward<Ts>(args)...);
}
//
//////////////////////////////////////////////////////////////////////////////////////

#include <boost/phoenix.hpp>
using boost::phoenix::arg_names::arg1;

int main()
{
    namespace fusion = boost::fusion;
    fusion::for_each(fun<fusion::vector<A, A, A>>(1,42,-99), std::cout << arg1 << "\n");
}

