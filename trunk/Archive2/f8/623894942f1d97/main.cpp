#include <type_traits>
#include <stdexcept>

template<class T>
struct forwarder {
    template<class U>
    typename std::enable_if<std::is_convertible<U, T>::value, T>::type
    operator()(U&& u) { return std::forward<U>(u); }
    
    T operator()(...) const {
        throw std::invalid_argument("forwarder called with unforwardable type");
    }
};

#include <iostream>
int main() {
    forwarder<int&> f;
    
    int x = 0;
    f(x)++;
    std::cout << x << "\n";
}