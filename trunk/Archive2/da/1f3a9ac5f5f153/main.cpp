#include <cassert>
#include <iostream>
#include <type_traits>
template <class Condition, class T = void>
using EnableIf = typename std::enable_if<Condition::value, T>::type;


template <class T>
using ToVoid = void;

template <class T, class Enable = void>
struct has_scalar : public std::false_type {};

template <class T>
struct has_scalar<T, ToVoid<typename T::Scalar>> : public std::true_type {};

template <class T, class Enable = void>
struct has_element : public std::false_type {};

template <class T>
struct has_element<T, ToVoid<typename T::Element>> : public std::true_type {};


template <class T, class Enable = void>
struct scalar_of;

template <class T>
struct scalar_of<T, EnableIf<has_element<T>>> {
    using type = typename T::Element;
};

template <class T>
struct scalar_of<T, EnableIf<has_scalar<T>>> {
    using type = typename T::Scalar;
};

template <class T>
using ScalarOf = typename scalar_of<T>::type;


struct BoostArray {
    using Element = double;
};

struct EigenArray {
    using Scalar = float;
};


int main() {
    using std::is_same;
    assert((is_same<double, ScalarOf<BoostArray>>::value));
    assert((is_same<float, ScalarOf<EigenArray>>::value));
    std::cout << "All is fine\n";
}