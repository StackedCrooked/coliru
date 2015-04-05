#include <algorithm>
#include <type_traits>

template<std::size_t tag = 0>
class Coord {
public:
    int x;
    int y;
    int z;

    constexpr Coord(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    
    template<typename T>
    auto operator*(const T factor) -> typename std::enable_if<std::is_arithmetic<T>::value, Coord<tag>>::type const {
        return {x * factor, y * factor, z * factor};
    }
};

int main() {
    Coord<0> c;
    c * 1;
    c * 1.0;
}
