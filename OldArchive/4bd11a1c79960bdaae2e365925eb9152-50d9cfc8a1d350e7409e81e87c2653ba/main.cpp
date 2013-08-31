#include <iostream>

template<typename T> struct FooObj;

template<> struct FooObj<int> {
  void func () const {
    std::cerr << "FooObj<int>::func" << std::endl;
  }
};

template<> struct FooObj<float> {
  void func () const {
    std::cerr << "FooObj<float>::func" << std::endl;
  }
};

struct FooStream {
  template<typename T>
  typename std::enable_if<std::is_constructible<FooObj<T>>::value, FooStream&>::type
  operator<< (T const& rhs) {
    this->operator<< (FooObj<T> (/* ... */));
    return *this;
  }

  template<typename T>
  typename std::enable_if<std::is_constructible<FooObj<T>>::value, FooStream&>::type
  operator>> (T const& rhs) {
    this->operator>> (FooObj<T> (/* ... */));
    return *this;
  }

  template<typename T>
  FooStream& operator<< (FooObj<T> const& rhs) {
    rhs.func ();

    return *this; 
  }

  template<typename T>
  FooStream& operator>> (FooObj<T> const& rhs) {
    rhs.func ();

    return *this; 
  }
};


int
main (int argc, char *argv[])
{
  FooObj<int> a;
  float       b;
  FooStream s;

  s << a << b >> b >> a;

  /* ERROR
      bool c;
      s >> c;
  */
}
