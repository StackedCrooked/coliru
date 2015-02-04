#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

template<class T>
struct Vector {
  typedef T value_type;

  Vector (int size) : _data {new T[size]}, _size {size} {}

  Vector (Vector const& data) : _data {new T[data._size]}, _size {data._size} { 
    std::copy (data._data.get (), data._data.get () + data._size, _data.get ());
  }

  Vector (Vector&& data) : _data (data._data.release ()), _size (data._size) { }


  T& operator[] (int idx) const {
    return _data[idx];
  }

  Vector& operator= (Vector&& value)  = default;
  Vector& operator= (Vector const& value) = delete;

  template<class Operation>
  Vector& operator= (Operation&& op) {
    _data.reset (new T[op._size]);
    _size = op._size;

    for (int i = 0; i < op._size; ++i) {
      _data[i] = op[i];
    }

    return *this;
  }

  std::unique_ptr<T[]> _data;
  int                _size;
};

template<class T>
Vector<T> sum (Vector<T> const& a, Vector<T> const& b) {
  Vector<T> ret (a._size);

  for (int i = 0; i < a._size; ++i)
    ret[i] = a[i] + b[i];

  return ret;
}

template<class V1, class V2, class T>
struct SumOp {
  typedef T value_type;

  inline T operator[] (int idx) const {
    return a[idx] + b[idx];
  }

  V1 const& a;
  V2 const& b;

  int _size;
};

template<class V1, class  V2>
SumOp<V1, V2, typename V1::value_type> sum_hack (V1 const& a, V2 const& b) {
  return { a, b, a._size };
}


int main () {
  auto print = [](Vector<int>& data) {
    for (int i = 0; i < data._size; ++i)
      std::cout << data[i] << ", ";

    std::cout << std::endl;
  };

  Vector<int> a(100), b(100), c(0);

  a[0] = 123;
  a[1] = 2;

  b[0] = 123;
  b[1] = 1;

  for (int i = 0; i < 10000000; ++i) {
    //c = sum (sum (a, b), sum (a, sum (a,b))); (old fashioned)
    c = sum_hack (sum_hack (a, b), sum_hack (a, sum_hack (a, b))); // fucking fuck
  }

  print (c);
}