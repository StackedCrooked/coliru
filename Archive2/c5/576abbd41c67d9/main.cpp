#include <iostream>
#include <type_traits>
#include <vector>

template <typename T> struct IsATemplate : std::false_type {};
template <template<typename,typename> class C, template<typename> class A, typename T>
struct IsATemplate<C<T, A<T>>> : std::true_type {};

template <typename T>
typename std::enable_if<IsATemplate<typename std::decay<T>::type>::value>::type
func(T&& c) {
    // usually I'd std::forward here, but let's just use cout...
    std::cout << c.size() << "\n";
}

int main() {
    func(std::vector<float>(2));
    std::vector<float> lv(3);
    func(lv);
}
