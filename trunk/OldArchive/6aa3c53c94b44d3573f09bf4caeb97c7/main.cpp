#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>

using namespace std;
using namespace boost::math::constants;
using namespace boost::multiprecision;

int main()
{
    cout << setprecision(100001)
		 << pi<number<cpp_dec_float<100000>>>()
		 << '\n';
}
