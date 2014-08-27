#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <iostream>
#include <map>

using Num = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<128>>;

int main()
{
    Num x("189.5307");

    std::map<Num, size_t> denoms;

    for (Num denom : { 
            Num("500."), Num("200."), Num("100."),
            Num("50."),  Num("20."),  Num("10."),
            Num("5."),   Num("2."),   Num("1."),
            Num(".5"),   Num(".2"),   Num(".1"),
            Num(".05"),  Num(".02"),  Num(".01"),
        })
    {
        Num count = x/denom;

        if (count >= 1)
        {
            count = trunc(count);
            std::cout << count << " * " << denom.str(2, std::ios::fixed) << "\n";
            x -= denom * count;
        }
    }

    std::cout << "Remainder: " << x << "\n";
}
