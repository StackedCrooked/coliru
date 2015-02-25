#include <iostream>
#include <string>

// The following would appear in your header file:
class Money {
  public:
    Money(double value, const std::string& code);

    const std::string& currencyCode() const;
    double value() const;

    friend std::istream& operator>>(std::istream&, Money&);
  private:
    double value_;
    std::string code_;
};

std::istream& operator>>(std::istream& in, Money& m);
std::ostream& operator<<(std::ostream& out, const Money& m);

// The following would appear in your source (.cpp) file:
Money::Money(double value, const std::string& code)
     : value_(value), code_(code) {}

const std::string& Money::currencyCode() const {
  return code_;
}

double Money::value() const {
  return value_;
}

std::istream& operator>>(std::istream& in, Money &m) {
  in >> m.value_ >> m.code_;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Money& m) {
  out << m.value() << " " << m.currencyCode();
  return out;
}

// And the following would either be in the same source file as above,
// or in another source file (e.g. main.cpp):

int main() {
    Money m(13.99, "GBP");
    std::cout << m << "\n";
    std::cin >> m;
    std::cout << m << "\n";
}