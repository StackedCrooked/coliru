#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
        boost::multiprecision::cpp_int f = 1;
        for(int n = 1; n <= 100; ++n)
            f *= n;
        std::cout << "factorial of 100 = " << f << '\n';
}
