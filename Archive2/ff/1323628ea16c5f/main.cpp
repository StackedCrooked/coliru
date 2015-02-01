template <class T> struct A { using X = typename T::X; };
template <class T> typename T::X f(typename A<T>::X);