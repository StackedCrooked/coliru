#include <type_traits>
#include <iostream>

namespace detail {
template<typename T>
inline auto do_shit(const T& t) -> decltype(t.test(), void()) {
    t.test();
}

template<typename T>
inline auto do_shit(const T& t) -> decltype(t.other(), void()) {
    t.other();
}

inline void do_shit(...) {
    std::cout << "nothing found\n";
}
} // detail

template<typename T>
inline auto do_shit(const T& t) -> decltype(detail::do_shit(t)) {
    return detail::do_shit(t);
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
