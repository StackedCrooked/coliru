#include <iostream>
#include <string>

template<typename T>
class Vector {
private:
T x, y, z;

public:
    Vector(T x, T y, T z) : x(x), y(y), z(z) {}
   // constructors, destructors, etc.

   T X() const { return ( this->x ); }
   T Y() const { return ( this->y ); }
   T Z() const { return ( this->z ); }

   template<typename U> auto operator+(const Vector<U> &v) const -> Vector<decltype(this->x + v.X())>
   {
       return ( Vector<decltype(this->x + v.X())>( this->x + v.X(), this->y + v.Y(), this->z + v.Z() ) );
   }
};

int main() {
    Vector<double> d1(1,2,3), d2(4,5,6);
    std::cout << (d1 + d2).X();
    Vector<int> d3(4,5,6);
    std::cout << (d1 + d3).X();
}
