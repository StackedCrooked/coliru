#include <iostream>
#include <type_traits>

using namespace std;

    template<int N>
    struct S{
        template <class T>
        typename std::enable_if<N == 1 && std::is_same<T, T>::value, int>::type
        f(T t) {return 1;}

        template <class T>
        typename std::enable_if<N != 1, T>::type
        f(T t) {return 0;}
    };

int main() {
    S<1> s1;
    S<2> s2;

    cout << s1.f(99) <<" "<< s2.f(99) << endl;
    return 0;
}
