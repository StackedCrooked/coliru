#include <utility>
#include <vector>
#include <iostream>

#define ANY_OP(T, OP) bool operator OP(T el) { \
   for (const auto& elem : _elems) { \
     if (elem OP el) return true; \
   } \
   return false; \
 }

template<class T>
class Any {
public:
  Any(std::initializer_list<T> elems) : _elems { elems }
  {}

  ANY_OP(T, ==)
  ANY_OP(T, >)
  ANY_OP(T, <)
private:
  std::vector<T> _elems;
};

int main() {
    Any<int> s = { 1, 2, 3 };
    std::cout << (s == 1) << std::endl;
    std::cout << (s > 10) << std::endl;
}