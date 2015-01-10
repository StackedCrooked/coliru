#include <type_traits>

template <typename T>
struct Vect3 {
    T a,b,c;

    template <typename U, typename V = typename std::common_type<T, U>::type>
        Vect3<V> operator*(U u) const { return  {a*u,b*u,c*u}; }

    template <typename U>
        Vect3& operator*=(U u) { a*=u; b*=u; c*=u; return *this; }
};

int main()
{
    auto f = Vect3<float>{1,2,3};
    auto d = 2.0;

    auto common = f * d; // fine!
    f *= d; // warns about possible loss of data in the instantion of operator*=
}
