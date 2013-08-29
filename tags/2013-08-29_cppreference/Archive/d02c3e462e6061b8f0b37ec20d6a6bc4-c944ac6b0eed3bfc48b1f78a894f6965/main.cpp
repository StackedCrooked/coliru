#include <iostream>
#include <type_traits>
#include <complex>

using namespace std;

template<bool B, typename T=void>
using Enable_if=typename std::enable_if<B,T>::type;

template<typename T>
constexpr bool Is_class() {
  return std::is_class<T>::value;
}

template<typename T>
class Smart_pointer {
public:
  explicit Smart_pointer(T* p) : data(p) {}
  Smart_pointer() : Smart_pointer(nullptr) {}

  T& operator*() const { return *data; }
  // template <class U=T,class=Enable_if<Is_class<U>()>>
  T* operator->() const { return data; }
  ~Smart_pointer() {
    delete data;
  }
private:
  T* data;  
};

int main() {
  Smart_pointer<double> p(new double);  //compiling error in g++ 4.7.2: no type named 'type' in 'struct std::enable_if<false, double>'
  // Smart_pointer<complex<double>> q(new complex<double>);//compile successfully.
  // q->imag();
  p->foo();
}
