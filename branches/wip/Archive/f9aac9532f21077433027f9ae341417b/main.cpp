#include <vector>
#include <iostream>

template <class T = const std::vector<int> &>
void f(T t) {
    std::cout << "f(T t)";
} // (1)

void f(const std::vector<int> &) {
    std::cout << "f()";
} // (2)

int main() {
   std::vector<int> x{5, 3, 2, 5, 6};

   f(x);
}