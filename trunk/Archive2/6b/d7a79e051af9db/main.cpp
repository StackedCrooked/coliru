#include <iostream>
#include <tuple>

template<typename T>
struct Adder
{
    const static int typeInfoSize = std::tuple_size<typename T::typeInfo>::value;

    T operator+(Adder<T>& rhs)
    {
        T sum;

        return sum;
    }
};

struct Vec4 { float x,y,z,w; };
struct Vec2 { float x,y; };

struct VertexData: public Adder<VertexData>
{
    /*Vec4 vertex;
    Vec2 texCoord;*/
    float x;
    double y;

    const static std::tuple<decltype(&VertexData::x), decltype(&VertexData::y)> typeInfo;
};

decltype(VertexData::typeInfo) VertexData::typeInfo(&VertexData::x, &VertexData::y);

int main()
{
    VertexData vd1; vd1.x = 1; vd1.y = 2;
    VertexData vd2; vd2.x = 4; vd2.y = 8;
    VertexData vd3 = vd1 + vd2;
    std::cout << vd3.x << std::endl;

    return 0;
}