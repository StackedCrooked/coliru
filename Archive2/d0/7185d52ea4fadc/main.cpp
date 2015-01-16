#include <vector>
#include <memory>
#include <iostream>

template <int>
struct dummy {};

template <typename T>
struct Value {
  
  template <size_t Size>
  Value(dummy<Size>) {
      value = new T[Size];
  }
  
  ~Value() {
      delete[] value;
  }
  
  T* value;
};

int main() {
    Value<int> blah(dummy<6>);
    
    return 0;
}