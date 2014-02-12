#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_dec_float.hpp>

#define rsa100 "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139"

using namespace std;
using namespace boost::multiprecision;

int main(){
    cpp_dec_float_100 n(rsa100);

    auto log       = boost::multiprecision::log(n);
    auto roundtrip = boost::multiprecision::exp(log);

    cout << std::fixed << log       << "\n";
    cout << std::fixed << roundtrip << "\n";
}
