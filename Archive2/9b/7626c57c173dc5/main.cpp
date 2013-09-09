#include <iostream>
#include <tuple>

template<typename T, typename Tuple, int index>
void memberWiseSum(T& lhs, T& rhs, T& sum, const Tuple& typeInfo)
{
    sum.*std::get<index>(typeInfo) = lhs.*std::get<index>(typeInfo) + rhs.*std::get<index>(typeInfo);
    //memberWiseSum<index - 1>(lhs, rhs, sum, typeInfo);
}

/*template<typename T, typename Tuple>
void memberWiseSum<T, Tuple, 0>(T& lhs, T& rhs, T& sum, const Tuple& typeInfo)
{
    sum.*std::get<0>(typeInfo) = lhs.*std::get<0>(typeInfo) + rhs.*std::get<0>(typeInfo);
}*/

template<typename T>
struct Adder
{
    T operator+(Adder<T>& rhs)
    {
        T sum;
        memberWiseSum< T, decltype(T::typeInfo), std::tuple_size<decltype(T::typeInfo)>::value - 1>(*static_cast<T*>(this),
                      *static_cast<T*>(&rhs), *static_cast<T*>(&sum), T::typeInfo);

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
    std::cout << vd3.y << std::endl;

    return 0;
}