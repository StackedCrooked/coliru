#include <type_traits>

#define requires(condition) \
    , typename = typename std::enable_if<(condition)>::type>

template<typename T>
bool constexpr PODType = std::is_pod<T>();

// example:
#include <cstring>
#include <string>

template<typename T, typename U
    requires (PODType<T> && PODType<U>)
T memcpy_cast(U&& from) {
    static_assert(sizeof(T) == sizeof(U));
    T to;
    std::memcpy(&to, &from, sizeof(to));
    return to;
}

int main() {
    memcpy_cast<unsigned>(42);
    // memcpy_cast<std::string>(42); // uncomment to see compilation fail
    // memcpy_cast<unsigned>(std::string()); // uncomment to see compilation fail
}