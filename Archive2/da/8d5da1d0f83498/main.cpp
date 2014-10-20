#include <complex>
#include <iostream>

namespace util {

template<typename T>
class real_proxy {
  std::complex<T> &_c;
public:
  real_proxy(std::complex<T> &c) : _c(c) {}
  void operator=(T t) { _c.real(t); }
};

template<typename T>
class imag_proxy {
  std::complex<T> &_c;
public:
  imag_proxy(std::complex<T> &c) : _c(c) {}
  void operator=(T t) { _c.imag(t); }
};

template<typename T>
real_proxy<T> real(std::complex<T> &c) {
  return real_proxy<T>(c);
}

template<typename T>
imag_proxy<T> imag(std::complex<T> &c) {
  return imag_proxy<T>(c);
}

}

int main() {
    std::complex<float> c;
    util::real(c) = 1.0f;
    util::imag(c) = 2.0f;
    
    std::cout << c << '\n';
}
