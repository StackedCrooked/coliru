#include <iostream>
#include <string>
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

struct Vec4: public Adder<Vec4>
{
    float x,y,z,w;
    
    std::string toString()
    {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + "}";
    }
    
    const static std::tuple<decltype(&Vec4::x), decltype(&Vec4::y), decltype(&Vec4::z), decltype(&Vec4::w)> typeInfo;
};

decltype(Vec4::typeInfo) Vec4::typeInfo(&Vec4::x, &Vec4::y, &Vec4::z, &Vec4::w);

struct Vec2: public Adder<Vec2>
{
    float x,y;
    
    std::string toString()
    {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }
    
    const static std::tuple<decltype(&Vec2::x), decltype(&Vec2::y)> typeInfo;
};

decltype(Vec2::typeInfo) Vec2::typeInfo(&Vec2::x, &Vec2::y);

struct VertexData: public Adder<VertexData>
{
    Vec4 vertex;
    Vec2 texCoord;
    
    std::string toString()
    {
        return "{" + vertex.toString() + ", " + texCoord.toString() + "}";
    }

    const static std::tuple<decltype(&VertexData::vertex), decltype(&VertexData::texCoord)> typeInfo;
};

decltype(VertexData::typeInfo) VertexData::typeInfo(&VertexData::vertex, &VertexData::texCoord);

int main()
{
    VertexData vd1; vd1.vertex.x = 1; vd1.vertex.y = 2; vd1.vertex.z = 3; vd1.vertex.w = 4;
    vd1.texCoord.x = 5; vd1.texCoord.y = 6;
    VertexData vd2; vd2.vertex.x = 1; vd2.vertex.y = 2; vd2.vertex.z = 3; vd2.vertex.w = 4;
    vd2.texCoord.x = 5; vd2.texCoord.y = 6;
    VertexData vd3 = vd1 + vd2;
    std::cout << vd3.toString() << std::endl;

    return 0;
}