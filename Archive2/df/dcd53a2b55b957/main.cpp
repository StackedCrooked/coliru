#include <algorithm>
#include <type_traits>

template<std::size_t tag = 0>
class Coord {
public:
    int x;
    int y;
    int z;

    constexpr Coord(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

    constexpr bool operator==(const Coord & rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    
    template<typename T>
    constexpr Coord<tag> operator^(const T factor) const {
        static_assert(std::is_arithmetic<T>::value, "you’re wrong");
        return Coord<tag>(x * factor, y * factor, z * factor);
    }
    
    template<typename T>
    auto operator%(const T factor) -> typename std::remove_reference<decltype(*this)>::type const {
        return typename std::remove_reference<decltype(*this)>::type(x * factor, y * factor, z * factor);
    }

    template<typename T>
    auto operator*(const T factor) -> typename std::enable_if<std::is_arithmetic<T>::value, typename std::remove_reference<decltype(*this)>::type>::type const {
        return typename std::remove_reference<decltype(*this)>::type(x * factor, y * factor, z * factor);
    }
};

int main() {
    Coord<0> c;
    c * 1;
    c * "";
    c % 1;
    c % "";
    c ^ 1;
    c ^ "";
}
