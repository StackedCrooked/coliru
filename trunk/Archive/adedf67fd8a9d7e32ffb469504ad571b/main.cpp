#include <iostream>
#include <type_traits>
#include <cmath>

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

    //Scalar division
    Vector2D& operator/= (T u) {
        this->x /= u;
        this->y /= u;
        return *this;
    }
    Vector2D operator/ (T u) const {
        Vector2D result(*this);
        return (result /= u);
    }

    friend std::ostream& operator<< (std::ostream& out, Vector2D& v) {
        out << '{' << v.x << ", " << v.y << '}';
        return out;
    }

    //Returns the length of the vector..
    T length() {
        return std::sqrt((*this) * (*this));
    }

    //Normalizes the vector
    Vector2D& normalize() {
        T length = this->length();
        if(length != 0 && length != 1) {
            this->x /= length;
            this->y /= length;
        }
        return *this;
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
    Vector2D<float> v = {16,19};
    v.normalize();
    std::cout << v;
}
