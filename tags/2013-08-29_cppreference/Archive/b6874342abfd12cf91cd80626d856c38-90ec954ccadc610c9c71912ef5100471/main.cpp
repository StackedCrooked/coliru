#include <initializer_list>

template <typename T>
std::initializer_list<T> list(std::initializer_list<T> l) { return l; }

template <typename T>
void f(T) {}

int main() {
    f(list({1,2,3,4,5}));
}