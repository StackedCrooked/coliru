#include <iostream>
#include <type_traits>
#include <tuple>

template<size_t... Ns>
struct indices {};

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N-1, N-1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<typename T, typename Tuple, size_t... Indices>
void memberWiseSum(T& lhs, T& rhs, T& sum, const Tuple& typeInfo, indices<Indices...>)
{
    using expander = int[];
    (void)expander{((sum.*std::get<Indices>(typeInfo) = lhs.*std::get<Indices>(typeInfo) + rhs.*std::get<Indices>(typeInfo)), 0)...};
}

template<typename T>
struct Adder
{
    T operator+(Adder<T>& rhs)
    {
        T sum;
        memberWiseSum(*static_cast<T*>(this), *static_cast<T*>(&rhs), *static_cast<T*>(&sum), T::typeInfo, build_indices<std::tuple_size<decltype(T::typeInfo)>::value>{});

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