#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_dec_float.hpp>

#define rsa100 "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139"

using namespace std;
using namespace boost::multiprecision;

int main(){
    cpp_dec_float_100 n(rsa100);

    auto log_n     = log(n);
    auto exp_log_n = exp(log_n);

    cout << std::fixed << log_n     << "\n";
    cout << std::fixed << exp_log_n << "\n";
}
