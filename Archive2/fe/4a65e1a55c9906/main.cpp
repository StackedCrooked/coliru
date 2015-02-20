#include <cstring>
#include <iostream>

template <std::size_t S>
struct helper {};

template <>
struct helper<1> {
    using type = uint8_t;
};
template <>
struct helper<2> {
    using type = uint16_t;
};
template <>
struct helper<4> {
    using type = uint32_t;
};
template <>
struct helper<8> {
    using type = uint64_t;
};

template <typename T>
using int_type = typename helper<sizeof(T)>::type;

template <typename T>
int_type<T> caster(const T& value) {
    int_type<T> v;
    static_assert(sizeof(value) == sizeof(v), "");
    std::memcpy(reinterpret_cast<char*>(&v), reinterpret_cast<const char*>(&value), sizeof(T));
    return v;
}

int main() {
    return caster(3.14f);
}
