#include <type_traits>

class Foo {
    struct Fallback {};

public:
    template<typename T, typename U, typename TT = void>
    using EnableIfSame =
        std::enable_if<
            std::is_same<T,U>::value ||
            std::is_same<T, Fallback>::value,
            TT>;

    template<typename T>
    void foo(T, typename EnableIfSame<T, char>::type* = nullptr) {}
};