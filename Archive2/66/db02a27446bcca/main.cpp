#include <iostream>
#include <type_traits>
#include <functional> 

template<typename T>
using const_ref_from_ref = typename std::add_const<typename std::remove_reference<T>::type>::type &;

struct X {
    int &i;

    X(int &ii) : i(ii) {}

//    auto acc() const -> std::add_const<const decltype((i))>::type { return i; } // fails the constness test
    auto acc() const -> const_ref_from_ref<decltype(i)> { return i; } // fails the constness test
//    const int &acc() const { return i; } // works as expected


};

void modify_const(const X &v) {
    static_assert(std::is_same<decltype(v.acc()), const int &>::value, "Not the same");
    v.acc() = 1;
}

int main() {
    int i = 0;
    X x(i);

    modify_const(x);
    std::cout << i << std::endl;

    return 0;
}