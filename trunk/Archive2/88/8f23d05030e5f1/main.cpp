#include <iostream>
#include <vector>

template<typename T>
void f(const std::vector<T>& a) {
    typename std::vector<T>::value_type b = a[0];
    std::cout << b << '\n';
}

int main() {
    std::vector<int> a = { 1, 2, 3};
    f(a);
}