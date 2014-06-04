#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <iostream>

using namespace boost::multiprecision;
using std::cout;
using std::endl;

typedef number<gmp_float<15>> mp_type;

int main()
{
    mp_type total("1.01");
    cout << total.str(0) << endl;
    mp_type first_addition(".01");
    cout << first_addition.str(0) << endl;
    total += first_addition;
    cout << total.str(0) << endl;
}