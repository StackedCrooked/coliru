#include <algorithm>
#include <type_traits>

template<std::size_t = 0>//tag
class Coord {
public:
    using Coordinate = Coord<>;
    using CoordOfCube = Coord<1>;
    using CoordInCube = Coord<2>;
    int x;
    int y;
    int z;

    constexpr Coord(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

    constexpr bool operator==(const Coord & rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    
    template<typename T>
    auto operator%(const T factor) -> typename std::remove_reference<decltype(*this)>::type const {
        return typename std::remove_reference<decltype(*this)>::type(x * factor, y * factor, z * factor);
    }

    template<typename T>
    auto operator*(const T factor) -> typename std::enable_if<std::is_arithmetic<T>::value, typename std::remove_reference<decltype(*this)>::type>::type const {
        return typename std::remove_reference<decltype(*this)>::type(x * factor, y * factor, z * factor);
    }
    template<typename T>
    auto operator*=(const T factor) -> typename std::enable_if<std::is_arithmetic<T>::value, typename std::remove_reference<decltype(*this)>::type>::type & {
        return *this = *this * factor;
    }

    template<typename T>
    auto operator/(const T divisor) -> typename std::enable_if<std::is_arithmetic<T>::value, typename std::remove_reference<decltype(*this)>::type>::type const {
        return typename std::remove_reference<decltype(*this)>::type(x / divisor, y / divisor, z / divisor);
    }
    template<typename T>
    auto operator/=(const T divisor) -> typename std::enable_if<std::is_arithmetic<T>::value, typename std::remove_reference<decltype(*this)>::type>::type & {
        return *this = *this / divisor;
    }

    /**
     * This function calculates the coordinates of the datacube from pixel coordinates
     */
    static Coordinate Px2DcCoord(Coordinate pxCoordinate, int cubeEdgeLength) {
        const auto cubeCoord = pxCoordinate.cube(cubeEdgeLength);
        return {cubeCoord.x, cubeCoord.y, cubeCoord.z};
    }

    constexpr Coordinate legacy2Global(const int cubeEdgeLength) const {
        return {x * cubeEdgeLength, y * cubeEdgeLength, z * cubeEdgeLength};
    }

    constexpr CoordOfCube cube(const int size) const {
        return {x / size, y / size, z / size};
    }

    constexpr CoordInCube insideCube(const int size) const {
        return {x % size, y % size, z % size};
    }

    Coordinate cap(const Coordinate & min, const Coordinate & max) const {
        Coordinate copy{*this};
        copy.x = std::max(min.x, std::min(copy.x, max.x));
        copy.y = std::max(min.y, std::min(copy.y, max.y));
        copy.z = std::max(min.z, std::min(copy.z, max.z));
        return copy;
    }
};

int main() {
    Coord<0> c;
    c * 1;
    c * "";
    c % 1;
    c % "";
}
