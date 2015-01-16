#include <iostream>
#include <string>
#include <map>
#include <type_traits>

using namespace std;

enum class A { min, i, j, k, max };
enum class B { min, x, y, z, max };

template <A>
struct Aattr {};

template<>
struct Aattr<A::i> {
    static constexpr const char* name = "A::i";
    static void f() { cout << name << endl; }
};

template<>
struct Aattr<A::j> {
    static constexpr const char* name = "A::j";
    static void f() { cout << name << endl; }
};

template<>
struct Aattr<A::k> {
    static constexpr const char* name = "A::k";
    static void f() { cout << name << endl; }
};

template <B>
struct Battr {};

template<>
struct Battr<B::x> {
    static constexpr const char* name = "B::x";
    static void f() { cout << name << endl; }
};

template<>
struct Battr<B::y> {
    static constexpr const char* name = "B::y";
    static void f() { cout << name << endl; }
};

template<>
struct Battr<B::z> {
    static constexpr const char* name = "B::z";
    static void f() { cout << name << endl; }
};

struct Attributes {
    string name;
};

ostream& operator<<(ostream& os, Attributes a) {
    return os << a.name;
}

template <A k>
Attributes GetAttr() {
    return { Aattr<k>::name };
}

template <B k>
Attributes GetAttr() {
    return { Battr<k>::name };
}

template <typename Enum>
using AttributeMap = map<Enum, Attributes>;

template <typename Enum>
constexpr Enum next(Enum v) {
    using UnderlyingType =
        typename underlying_type<Enum>::type;
    return static_cast<Enum>(
        static_cast<UnderlyingType>(v) + 1);
}

// there are some restrictions around non-type template arguments,
// therefore we use a type, integral_constant, as second argument
// istead of the value directly
template <typename Enum, typename Index>
struct MapBuilder {
    using MapType = AttributeMap<Enum>;
    static MapType build() {
        MapType result = MapBuilder<Enum, NextIndex>::build();
        result.insert({Index::value, GetAttr<Index::value>()});
        return result;
    }
private:
    using NextIndex = integral_constant<Enum, next(Index::value)>;
};

template <typename Enum>
struct MapBuilder<Enum, integral_constant<Enum, Enum::max>> {
    using MapType = AttributeMap<Enum>;
    static MapType build() {
        return {};
    }    
};

template <typename Enum>
AttributeMap<Enum> BuildMap() {
    return MapBuilder<Enum, integral_constant<Enum, next(Enum::min)>>::build();
}

template <typename Enum>
void PrintMap(map<Enum, Attributes> m) {
    for (const auto& kv : m)
        cout << kv.second.name << " ";
    cout << endl;
}

int main()
{
    auto  mapA = BuildMap<A>();
    PrintMap(mapA);

    auto  mapB = BuildMap<B>();
    PrintMap(mapB);
}
