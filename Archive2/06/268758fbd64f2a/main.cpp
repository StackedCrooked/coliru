    #include <iostream>
    #include <cstddef>
    #include <array>
    #include <string>
     
    template <typename... T>
    class Foo {
    public:
    static constexpr std::array<size_t, sizeof...(T)> sizes { sizeof(T)... };
    };
     
    using X = Foo<char, int, double, float, std::string, unsigned>;
     
    template <typename... T>
    constexpr std::array<size_t, sizeof...(T)> Foo<T...>::sizes;
     
    int main() {
     
    for (auto s : X::sizes) {
    std::cout << s;
    }
     
    return 0;
    }