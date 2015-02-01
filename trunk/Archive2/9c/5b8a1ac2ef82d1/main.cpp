template <class T> struct A { using X = typename T::X; };
template <class T> typename T::X f(typename A<T>::X);
template <class T> void f(...) {}
template <class T> auto g(typename A<T>::X) -> typename T::X;
template <class T> void g(...) {}

void h() {
    f<int>(0); // OK, substituting return type causes deduction to fail
    g<int>(0); // error, substituting parameter type instantiates A<int>
}