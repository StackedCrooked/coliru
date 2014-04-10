#include <iostream>
#include <boost/utility/value_init.hpp>

struct Money
{
    boost::value_initialized<double> amountP, amountG, totalChange;
    boost::value_initialized<int> twenty, ten, five, one, change;
    boost::value_initialized<int> quarter, dime, nickel, penny;

    void foo();
    Money() {
        std::cout << amountP << ' ' << amountG << ' ' << totalChange << '\n';
        std::cout << twenty << ' ' << ten << ' ' << five << ' ' << one << ' ' << change << '\n';
        std::cout << quarter << ' ' << dime << ' ' << nickel << ' ' << penny << '\n';
    }
};

int main() {
    Money m;   
}