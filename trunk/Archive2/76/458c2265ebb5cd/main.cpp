#include <iostream>
#include <tuple>

template< typename T, template<typename U, typename V> std::tuple<U, V> >
struct Adder
{
    Adder<T> operator+(Adder<T>& rhs)
    {
        (*this).U + rhs.U;
        (*this).V + rhs.V;
    }
};

struct Vec4 { float x,y,z,w; };
struct Vec2 { float x,y; };

struct VertexData: public Adder<VertexData,
        std::tuple<VertexData::x, VertexData::y>>
{
    /*Vec4 vertex;
    Vec2 texCoord;*/
    float x;
    double y;
};

int main()
{
    VertexData vd1;
    VertexData vd2;
    vd1 + vd2;

    return 0;
}