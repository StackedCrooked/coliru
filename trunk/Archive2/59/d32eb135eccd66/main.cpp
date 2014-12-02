
#include <cstddef>
#include <cstdint>
#include <string>
#include <functional>

template <typename T> void f(T, T, bool, bool) {}    

template<typename T> void h(T&&) {}
// template<typename T> void h(T) {} // works 

void g() {
  h(f<std::string>);
}

int main(){}