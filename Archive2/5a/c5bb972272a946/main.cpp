#include <iostream>
#include <sstream>
#include <string>

// http://en.wikipedia.org/wiki/ISO_4217

enum CCY_ID {
    ccy_AUD =  36, // Australian dollar
    ccy_CAD = 124, // Canadian dollar
    ccy_CNY = 156, // Chinese yuan
    ccy_JPY = 392, // Japanese yen
    ccy_CHF = 756, // Swiss franc
    ccy_GBP = 826, // Pound sterling
    ccy_USD = 840, // United States dollar
    ccy_EUR = 978, // Euro
    ccy_BRL = 986, // Brazilian real
};

template<size_t CCY> class Money;
using BRL = Money<ccy_BRL>; // Brazilian real
using CAD = Money<ccy_CAD>; // Canadian dollar
using CHF = Money<ccy_CHF>; // Swiss franc
using CNY = Money<ccy_CNY>; // Chinese yuan
using GBP = Money<ccy_GBP>; // Pound sterling
using JPY = Money<ccy_JPY>; // Japanese yen
using AUD = Money<ccy_AUD>; // Australian dollar
using EUR = Money<ccy_EUR>; // Euro
using USD = Money<ccy_USD>; // United States dollar

template<size_t N>
class Money {
    double _amount;
    std::string ccy_symbol() const {
        switch(N) {
        case ccy_AUD: return "_AUD";
        case ccy_CAD: return "_CAD";
        case ccy_CNY: return "_CNY";
        case ccy_JPY: return "_JPY";
        case ccy_CHF: return "_CHF";
        case ccy_GBP: return "_GBP";
        case ccy_USD: return "_USD";
        case ccy_EUR: return "_EUR";
        case ccy_BRL: return "_BRL";
        default: throw;
        }
    }
public:
    constexpr Money( double x ) : _amount(x) {}
    template<size_t M> constexpr Money( const Money<M> & m );
    constexpr double operator()() const { return _amount; }
    std::string to_string() const {
        std::ostringstream sstream;
        sstream << _amount << ccy_symbol();
        return sstream.str();
    }
    constexpr CCY_ID ccy_id() const { return reinterpret_cast<CCY_ID>(N); }
};

template<>
template<>
EUR::Money( const USD & m ) : _amount(0.74*m()) {
//    std::cout << "Converting " << m() << " USD to " << _amount << " Euros." << std::endl;
}

template<size_t N>
struct Currency {};

constexpr USD EURUSD( EUR x ) { return USD(1.3081 * x()); }
constexpr EUR USDEUR( USD x ) { return EUR(0.74 * x()); }

constexpr USD operator"" _USD(const long double x) { return USD(x); }
constexpr EUR operator"" _EUR(const long double x) { return EUR(x); }

template<size_t T>
std::ostream &
operator<< ( std::ostream &o, const Money<T> &ccy )
{
    o << ccy.to_string();
    return o;
}

int main() {
    try {
        USD buying_power(1000.00);
        auto amount = 1000.00_USD;
        std::cout << "amount=" << EUR(amount) << std::endl;
        std::cout << "buying_power=" << EUR(buying_power) << std::endl;
    } catch (...) {
        std::cerr << "Exception received" << std::endl;
    }
    return 0;
}
