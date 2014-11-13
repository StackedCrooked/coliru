#include <iostream>
#include <cmath>
#include <tuple>
using std::cout;
using std::endl;

namespace geometry
{
    namespace coordinate
    {
        template<typename T, template<typename> class Implementation>
        class Coordinate:
        private Implementation<T>
        {
            public:
            Coordinate(T c0, T c1, T c2): Implementation<T>(c0, c1, c2) {}
            
            template<typename TT, template<typename> class I>
            Coordinate(Coordinate<TT, I> const& coordinate)
            : Implementation<T>(coordinate)
            {}
            
            using Implementation<T>::x;
            using Implementation<T>::y;
            using Implementation<T>::z;
            
            using Implementation<T>::r;
            using Implementation<T>::t;
            using Implementation<T>::p;
            
            protected:
            using Implementation<T>::write;
            
            private:
            template<typename TT, template<typename> class I>
            friend std::ostream& operator<<(std::ostream& stream, Coordinate<TT, I> const& coordinate);
            
        };
        
        template<typename T, template<typename> class I>
            std::ostream& operator<<(std::ostream& stream, Coordinate<T, I> const& coordinate)
            {
                coordinate.write(stream);
                return stream;
            }
        
        template<typename T>
        class Cartesian
        : private std::tuple<T, T, T>
        {
            public:
            Cartesian(T x, T y, T z): std::tuple<T, T, T>(x, y, z) {}
            
            template<typename TT, template<typename> class I>
            Cartesian(Coordinate<TT, I> const& coordinate):
            Cartesian(coordinate.x(), coordinate.y(), coordinate.z())
            {}
                
            protected:
            T const& x() const { return std::get<0>(*this); }
            T const& y() const { return std::get<1>(*this); }
            T const& z() const { return std::get<2>(*this); }
            
            T& x() { return std::get<0>(*this); }
            T& y() { return std::get<1>(*this); }
            T& z() { return std::get<2>(*this); }
            
            T r() const { return std::sqrt(x()*x() + y()*y() + z()*z()); }
            T t() const { return r() * std::acos(z() / r()); }
            T p() const { return r() * std::atan(y() / x()); }
            
            void write(std::ostream& stream) const
            {
                stream << '('
                << "x:" << x() << ','
                << "y:" << y() << ','
                << "z:" << z() << ')';
            }
            
            private:
            
        };
        
        template<typename T>
        class Spherical
        : private std::tuple<T, T, T>
        {
            public:
            Spherical(T r, T t, T p): std::tuple<T, T, T>(r, t, p) {}
            
            template<typename TT, template<typename> class I>
            Spherical(Coordinate<TT, I> const& coordinate):
            Spherical(coordinate.r(), coordinate.t(), coordinate.p())
            {}
            
            protected:
            T const& r() const { return std::get<0>(*this); }
            T const& t() const { return std::get<1>(*this); }
            T const& p() const { return std::get<2>(*this); }
            
            T& r() { return std::get<0>(*this); }
            T& t() { return std::get<1>(*this); }
            T& p() { return std::get<2>(*this); }
            
            T x() const { return r() * std::sin(t()) * std::sin(p()); }
            T y() const { return r() * std::sin(t()) * std::cos(p()); }
            T z() const { return r() * std::cos(t()); }
            
            void write(std::ostream& stream) const
            {
                stream << '('
                << "r:" << r() << ','
                << "t:" << t() << ','
                << "p:" << p() << ')';
            }
            
            private:
        };
        
        template <typename T> using CartesianCoordinate = Coordinate<T, Cartesian>;
        template <typename T> using SphericalCoordinate = Coordinate<T, Spherical>;
    } //namespace coordinate
 
} //namespace geometry


int main()
{
    using namespace geometry::coordinate;
    CartesianCoordinate<double> c(1, 2, 3);
    SphericalCoordinate<double> s(c);
    cout << c << endl << s << endl;

    return 0;
}