#include <iostream>
#include <tuple>

template< typename T, typename... Members>
struct Adder
{
    Adder<T, Members...> operator+(Adder<T, Members...>& rhs)
    {
        sizeof...(Members);
        /*(*this).*U + rhs.*U;
        (*this).*V + rhs.*V;*/
    }
};

struct Vec4: public Adder<Vec4> { float x,y,z,w; };
struct Vec2 { float x,y; };

struct VertexData: public Adder<VertexData, &VertexData::x>
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