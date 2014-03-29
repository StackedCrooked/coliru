#include <iostream>
#include <type_traits>

struct nonnegative {
    nonnegative() = default;
    template <typename T,
              typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
    nonnegative(T value) : value{value} {}

    operator unsigned () const { return value; }

private:
    unsigned value;
};

void f(nonnegative x) {
    std::cout << x << '\n';
}

int main() {
    f(23u); // works
    f(23); // fails
}