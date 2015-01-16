#include <vector>
#include <memory>
#include <iostream>

template <typename T>
struct Value {
  
  template <size_t Size>
  Value() {
      value = new T[Size];
  }
  
  ~Value() {
      delete[] value;
  }
  
  T* value;
};

int main() {
    // how to instantiate Value<int><5> ??
    
    return 0;
}