
#include <iostream>
#include <memory>
#include <functional>

template<class T> constexpr std::size_t how_many_elements(std::size_t bytes) {
  return (bytes - (!std::is_trivially_destructible<T>::value*sizeof(void*))) / sizeof(T);
}

struct MyClass {
    struct empty {} realempty;
    int x;
    empty otherempty;
  char a, b, c;
  virtual ~MyClass() {}
    void *operator new[](std::size_t count) {
        void *p = ::operator new[](count);
        std::cout << "allocating " << count << " bytes, " << how_many_elements<MyClass>(count) << " items\n";
        return p;
    }
};

int main() {
  struct xx {} xxx;
  std::cout << "xx = " << sizeof(xx) << "\n" << "xxx = " << sizeof(xxx) << "\n";
  std::cout << "xx = " << alignof(xx) << "\n" << "myclass = " << alignof(MyClass) << "\n";
  for( auto count : { 1, 5, 10, 100, 1000 } ) {
    std::cout << "allocating " << sizeof(MyClass) << " * " << count << " items\n";
    auto x = new MyClass[count];
    delete[] x;
  }
}
