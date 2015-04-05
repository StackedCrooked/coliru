#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>

namespace mp = boost::multiprecision;

template <typename backend, bool with_et>
void run() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    using BF = typename mp::number<backend, with_et? mp::et_on : mp::et_off>;
    std::cout << "\t" << ceil(BF(18)/6) << "\n";
    std::cout << "\t" << ceil(BF(18)/BF(6)) << "\n";
}

int main() {
    run<mp::cpp_dec_float<100>, mp::et_on> ();
    run<mp::cpp_bin_float<100>, mp::et_on> ();
    run<mp::cpp_dec_float<100>, mp::et_off>();
    run<mp::cpp_bin_float<100>, mp::et_off>();
}
