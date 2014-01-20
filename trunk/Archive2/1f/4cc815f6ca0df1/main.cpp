#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace boost::multiprecision;

int main() {
    cpp_rational a("4561231231235/123123123123");
    cpp_int v = numerator(a)/denominator(a);
    std::cout << "convert: " << v.convert_to<int>() << "\n";

    a = cpp_rational("456/123");
    v = numerator(a)/denominator(a);
    std::cout << "convert: " << v << "\n";
}
