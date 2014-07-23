template<typename T>
struct storage {
    const T* ptr;
    storage(const T& x): ptr(&x) {}
};

template<typename T>
storage<T> make_storage(const T& t) {
    return { t };
}

#include <iostream>

int main() {
    auto&& s = make_storage(42);
    std::cout << *(s.ptr);
}