#include <complex>
#include <type_traits>
#include <boost/type_traits.hpp>

int main()
{
    static_assert(std::is_floating_point<float>::value, "some message");
    static_assert(std::is_floating_point<double>::value, "some message");
    static_assert(boost::is_complex<std::complex<float>>::value, "some message");
    static_assert(boost::is_complex<std::complex<double>>::value, "some message");
}