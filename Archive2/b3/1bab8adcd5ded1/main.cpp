#include <iostream>
#include <typeinfo>
template<typename T> struct lol {
    template<typename U> lol(U u);
};
template<typename T> template<typename U> lol<T>::lol(U u) {
    std::cout << typeid(T).name() << typeid(U).name();
}
int main() {
    lol<int> lol(1.0);
}