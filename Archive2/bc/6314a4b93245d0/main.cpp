#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>

using namespace boost::multiprecision;
using std::cout;
using std::endl;

typedef cpp_dec_float_50 mp_type;

int main()
{
    mp_type total("1.01");
    cout << total.str(0) << endl;
    mp_type first_addition(".01");
    cout << first_addition.str(0) << endl;
    total += first_addition;
    cout << total.str(0) << endl;
}
