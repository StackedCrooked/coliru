#include <type_traits>
#include <iostream>

template<typename C, typename T = int>
using EnableIf = typename std::enable_if<C::value, T>::type;

template<unsigned int N>
struct choice : choice<N + 1> {};

// terminate here -- 7 different overloads is currently enough for all use cases.
template<>
struct choice<6> {};

struct select_overload : choice<0> {};

struct otherwise {
    otherwise(...) {}
};

namespace detail {
template<typename T>
inline auto do_shit(const T& t, choice<0>) -> decltype(t.test(), void()) {
    t.test();
}

template<typename T>
inline auto do_shit(const T& t, choice<1>) -> decltype(t.other(), void()) {
    t.other();
}

template<typename T>
inline void do_shit(const T&, otherwise) {
    std::cout << "nothing found\n";
}
} // detail

template<typename T>
inline auto do_shit(const T& t) -> decltype(detail::do_shit(t, select_overload{})) {
    return detail::do_shit(t, select_overload{});
}

struct one {
    void test() const {
        std::cout << "one::test\n";
    }
};

struct two {
    void other() const {
        std::cout << "two::other\n";
    }
};

struct three {
    void test() const {
        std::cout << "three::test\n";
    }

    void other() const {
        std::cout << "three::other\n";
    }
};

struct lol {};

int main(){
    do_shit(one{});
    do_shit(two{});
    do_shit(three{});
    do_shit(lol{});
}
