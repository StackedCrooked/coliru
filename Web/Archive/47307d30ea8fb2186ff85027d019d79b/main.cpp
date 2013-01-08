#include <iostream>
#include <type_traits>

template <typename T>
struct Point {
    static_assert(std::is_arithmetic<T>::value, "Points must be integral or floating types.");
    T x;
    T y;
    Point(): x(0), y(0) {}
    Point(T a, T b = 0): x(a), y(b) {}
    Point& operator+= (const Point& u) {
        this->x += u.x;
        this->y += y.x;
        return *this;
    }
};

int main() {
    Point<int> v(15,6);
    Point<int> u(8,15);
    v += u;
    std::cout << v.x << '\n' << v.y << '\n';
}