#include <type_traits>

template<class T>
struct A {
    typename std::enable_if<!std::is_unsigned<T>::value,A>::type operator-() {return {};}
};

int main() {
    A<unsigned> a=a;
}