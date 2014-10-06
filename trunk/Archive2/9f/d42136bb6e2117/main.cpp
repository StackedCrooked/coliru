#include <iostream>
#include <stdexcept>
#include <string>

#define CHAR char
#define ATOL atol
#define MAIN main

using overflow_error = std::runtime_error;
using std::cerr;
using std::cout;
using std::endl;

class SixFactor {
public:
    SixFactor(const ulong m, const int o): _mult(m), _offs(o) {};
    
    SixFactor operator*(const SixFactor &othr) throw(overflow_error) {
#if 0
        throw overflow_error("this works");
#else
        std::string err_msg = "SixFactor mult. overflow of (";
        err_msg += static_cast<std::string>(*this) + ") * (" +
        static_cast<std::string>(othr) + ")";
        cerr << "throwing an exception: " << err_msg << endl;
        throw std::overflow_error(err_msg.c_str());
#endif        
    }
    
    long mult() const noexcept { return _mult; }
    long offs() const noexcept { return _offs; }
    
    operator std::string() const {
        auto result = std::to_string(_mult);
        if (_offs < 0) result += " - " + std::to_string(-_offs);
        else result += " + " + std::to_string(_offs);
        return result;
    }
private:
    long _mult, _offs;
};

std::ostream& operator <<(std::ostream &lhs, const SixFactor &rhs) {
    auto offs = rhs.offs();
    lhs << rhs.mult();
    offs < 0 ? (lhs << " - " << -offs ) : (lhs << " + " << offs);

    return lhs;
}

int MAIN(int argc, CHAR* argv[])
{
  SixFactor t(26757, -1);
  cout << "t = " << static_cast<std::string>(t) << endl;
  try {
    SixFactor e(0,0);
    e = t*t;
    cout << "got here - no exception" << endl;
  } catch (overflow_error &oe) {
    cout << "caught overflow exception: " << oe.what() << endl;
  } catch (...) {
    cout << "caught an unknown exception" << endl;
  }
  return 0;
}