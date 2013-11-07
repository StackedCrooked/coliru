#include "boost/variant.hpp"
#include <iostream>
#include <complex>

struct structy {
    int a;
    
    friend std::ostream &operator<<(std::ostream &out, structy) {
        return out;
    }
};

void times_two(
        boost::variant<int, std::string, std::complex<double>, structy> & v) {
    if (int* pi = boost::get<int>(&v))
        *pi *= 2;
    else if (std::string* pstr = boost::get<std::string>(&v))
        *pstr += *pstr;
    //No check for complex or structy - should silently returns.
}

int main() {

    boost::variant<int, std::string, std::complex<double>, structy> v;
    v = "hello";
    std::string& str = boost::get<std::string>(v);
    str += " world! ";
//As desired, the std::string contained by v now is equal to "hello world! ". Again, we can demonstrate this by streaming v to standard output:
    std::cout << v << std::endl;
    times_two(v);
    std::cout << v << std::endl;
    std::complex<double> a(5.0, 6.0);
    v = a;
    times_two(v);
    return 0;
}