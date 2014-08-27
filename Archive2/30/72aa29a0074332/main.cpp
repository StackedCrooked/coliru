#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <iostream>

using Num = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<128>>;

int main()
{
    Num x("189.5307");

    for (Num denom : { 
            Num("500.00"),   Num("200.00"),   Num("100.00"),
             Num("50.00"),    Num("20.00"),    Num("10.00"),
              Num("5.00"),     Num("2.00"),     Num("1.00"),
              Num("0.50"),     Num("0.20"),     Num("0.10"),
              Num("0.05"),     Num("0.02"),     Num("0.01"),
        })
    {
        Num count = x/denom;

        if (count >= 1)
        {
            count = trunc(count);
            std::cout << count << " * " << std::right << std::setw(6) << denom.str(2, std::ios::fixed) << "\n";
            x -= denom * count;
        }
    }

    std::cout << "Remainder: " << x << "\n";
}
