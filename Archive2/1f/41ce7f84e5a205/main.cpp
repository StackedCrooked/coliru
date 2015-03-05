#include <iostream>
#include <memory>
#include <type_traits>

struct crap {
    unsigned ref_count;
};

template <typename T>
struct crap_ptr {
    crap_ptr(T*) {
        std::cout << "This pointer is crap.\n";
    }
};

template <typename T, bool Crap = std::is_base_of<crap, T>::value>
struct ptr_helper {
    using type = std::shared_ptr<T>;
};

template <typename T>
struct ptr_helper<T, true> {
    using type = crap_ptr<T>;
};

template <typename T>
using ptr = typename ptr_helper<T>::type;

struct foo : crap { };

int
main() {
    ptr<int> p{new int};
    ptr<foo> q{new foo};
}
