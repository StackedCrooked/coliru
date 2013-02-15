#include <iostream>
#include <type_traits>
#include <cmath>

template <typename T>
struct Vector2D {
    const double myPi = 3.14159265358979323;
    static_assert(std::is_arithmetic<T>::value, "Euclidean Vectors must be integral or floating types.");
    T x;
    T y;
    Vector2D(): x{0}, y{0} {}
    Vector2D(T a, T b = 0): x{a}, y{b} {}

    //Operators

    //Addition
    Vector2D& operator+= (const Vector2D& u) {
        x += u.x;
        y += u.y;
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
        x -= u.x;
        y -= u.y;
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
        x *= u;
        y *= u;
        return *this;
    }
    Vector2D operator* (T u) const {
        Vector2D result(*this);
        return (result *= u);
    }

    //Scalar division
    Vector2D& operator/= (T u) {
        x /= u;
        y /= u;
        return *this;
    }
    Vector2D operator/ (T u) const {
        Vector2D result(*this);
        return (result /= u);
    }

    //Vector division
    Vector2D& operator/= (const Vector2D& u) {
        x /= u.x;
        y /= u.y;
        return *this;
    }
    Vector2D operator/ (const Vector2D& u) {
        Vector2D result(*this);
        return (result /= u);
    }

    //Comparison overloads
    bool operator== (const Vector2D& v) const {
        return (v.x == x && v.y == y);
    }

    bool operator!= (const Vector2D& v) const {
        return (v.x != x || v.y != y);
    }

    friend std::ostream& operator<< (std::ostream& out, Vector2D& v) {
        out << '{' << v.x << ", " << v.y << '}';
        return out;
    }

    //Returns the length of the vector..
    T length() {
        return std::sqrt((*this) * (*this));
    }

    //Distance function to another vector.
    T distance(const Vector2D& u) {
        T a = u.x - x;
        T b = u.y - y;
        return std::sqrt((a * a) + (b * b));
    }

    //Normalizes the vector
    Vector2D& normalize() {
        T length = this->length();
        if(length != 0 && length != 1) {
            x /= length;
            y /= length;
        }
        return *this;
    }

    //Direction of the vector
    Vector2D& direction(const Vector2D& u) {
        *this = u - *this;
        this->normalize();
        return *this;
    }

    //Angle between two vectors, returns radians.
    T angle(Vector2D& u) {
        return std::acos(((*this) * u) / (this->length() * u.length()));
    }

    T angleDegrees(Vector2D& u) {
        T radians = this->angle(u);
        return (radians*180)/myPi;
    }

    bool isUnitVector() const {
        return (x * x + y * y) == 1;
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

//Distance function
template<typename T>
T distance(const Vector2D<T>& u, const Vector2D<T>& v) {
    T a = v.x - u.x;
    T b = v.y - u.y;
    return std::sqrt((a * a) + (b * b));
}

int main() {
    Vector2D<float> v = {0,0};
    Vector2D<float> u = {1,5};
    std::cout << v.angle(u);
}


