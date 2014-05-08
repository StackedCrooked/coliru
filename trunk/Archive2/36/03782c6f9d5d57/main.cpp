#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/number.hpp>
#include <vector>

using boost::multiprecision::mpq_rational;

template <typename rational>
inline int round_to_int(rational v)
{
    v = v + typename rational::number(v.sign()) / 2;
    return v.template convert_to<int>();
}

int main()
{
    auto show = [](mpq_rational a) { 
        std::cout << std::right << a << "\t" << std::setw(6) << (double) a << "\t" << std::right << std::setw(6) << round_to_int(a) << '\n';
    };
    std::cout << std::fixed << std::setprecision(2);

    for (mpq_rational r("-2"); r<=2; r = (r*7+1)/7)
        show(r);
    std::cout << "----------------------\n";
    for (mpq_rational r("-2"); r<=2; r = (r*2+1)/2)
        show(r);
}
