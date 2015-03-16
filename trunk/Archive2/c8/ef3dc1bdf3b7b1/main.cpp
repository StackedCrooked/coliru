#include <utility>
#include <cstddef>
#include <iostream>

using std::size_t;

template<class T>
std::remove_cv_t<T> copy(T& t) {
  return t;
}
template<class T>
void copy(T&&)=delete; // block rvalue copy
template<class T, size_t N>
void copy(T(&)[N]) = delete; // we can implement this if we want: see below

int main() {
    int x = 0;
    auto f = [&]() mutable {
        auto y = copy(x);
        std::cout << y << "\n";
    };
    f();
}