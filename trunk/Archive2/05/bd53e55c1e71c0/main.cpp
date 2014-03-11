#include <type_traits>

class Foo {
    struct Fallback {};

public:
    template<typename T, typename U>
    using EnableIfSame =
        std::enable_if<
            std::is_same<T,U>::value ||
            std::is_same<T, Fallback>::value>;

    template<typename T>
    void foo(T, EnableIfSame<T, char>* = nullptr) {}
};