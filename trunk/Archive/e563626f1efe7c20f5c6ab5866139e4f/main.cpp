#include <iostream>
#include <type_traits>

template <typename T>
struct Vector2D {
    static_assert(std::is_arithmetic<T>::value, "Euclidean Vectors must be integral or floating types.");
    T x;
    T y;
    Vector2D(): x(0), y(0) {}
    Vector2D(T a, T b = 0): x(a), y(b) {}

    //Operators
    Vector2D& operator+= (const Vector2D& u) {
        this->x += u.x;
        this->y += u.y;
        return *this;
    }
    Vector2D operator+ (const Vector2D& u) const {
        Vector2D result(*this);
        return (result += u);
    }
    Vector2D operator+ (T u) const {
        Vector2D result(*this);
        return (result += Vector2D(u,u));
    }
    Vector2D& operator-= (const Vector2D& u) {
        this->x -= u.x;
        this->y -= u.y;
        return *this;
    }
    Vector2D operator- (const Vector2D& u) const {
        Vector2D result(*this);
        return (result -= u);
    }
    Vector2D operator- (T u) const {
        Vector2D result(*this);
        return (result -= Vector2D(u,u));
    }
};

int main() {
    Vector2D<int> v(15,6);
    Vector2D<int> u(8,15);
    Vector2D<int> k = u + 4;
    Vector2D<int*> w;
    std::cout << k.x << '\n' << k.y << '\n';
}