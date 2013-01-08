#include <iostream>
#include <type_traits>

template <typename T>
struct Vector2D {
    static_assert(std::is_arithmetic<T>::value, "Euclidean Vectors must be integral or floating types.");
    T x;
    T y;
    Vector2D(): x{0}, y{0} {}
    Vector2D(T a, T b = 0): x{a}, y{b} {}

    //Operators

    //Addition
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

    //Subtraction
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

    //Scalar multiplication
    Vector2D& operator*= (T u) {
        this->x *= u;
        this->y *= u;
        return *this;
    }
    Vector2D operator* (T u) const {
        Vector2D result(*this);
        return (result *= u);
    }
};

template<typename T>
Vector2D<T> operator+ (T u, const Vector2D<T>& v) {
    return v + u;
}

template<typename T>
Vector2D<T> operator- (T u, const Vector2D<T>& v) {
    return v - u;
}

template<typename T>
Vector2D<T> operator* (T u, const Vector2D<T>& v) {
    return v * u;
}

//Dot product
template<typename T>
T operator* (const Vector2D<T>& u, const Vector2D<T>& v) {
    return (u.x*v.x + v.y*u.y);
}

int main() {
    Vector2D<int> u = {9,10};
    Vector2D<int> v = {16,19};
    auto z = v * u;
    std::cout << z;
}
