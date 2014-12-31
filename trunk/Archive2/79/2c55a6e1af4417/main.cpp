#include <vector>
#include <iostream>


template<typename X, typename COLLECTION, typename RET_TYPE = void>
struct enable_if_is_base_of : std::enable_if<std::is_base_of<X, COLLECTION>::value, RET_TYPE>
{};

class A {};
template <typename X>
class B {};
class C {};
template <typename X>
class D {};

template <typename X>
class container : A, B<X> {};

template <typename X, typename Y>
typename enable_if_is_base_of<X, container<Y>>::type fn(X&& x) { }

int main() {

    fn<B<int>, int>(B<int>()); // Ok
    fn<B<int>, int>(C()); // Fails as expected
    return 0;
}