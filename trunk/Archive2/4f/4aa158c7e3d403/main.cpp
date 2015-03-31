#include <iostream>
#include <tuple>

template<class T>
struct TupleComparable
{
    bool operator==(const TupleComparable& other) const {
        return static_cast<const T&>(*this).toTuple() == static_cast<const T&>(other).toTuple();
    }
};

struct Foo : public TupleComparable<Foo>
{
    Foo(int a, int b) : a{a}, b{b} {}
    
    std::tuple<const int&, const int&> toTuple() const {
        return std::tie(a, b);
    }

    int a;
    int b;
};

int main(void)
{
    auto f = Foo{10,20};
    auto g = Foo{10,21};
    auto h = Foo{11,20};
    
    std::cout << (f == f) << std::endl;
    std::cout << (f == g) << std::endl;
    std::cout << (f == h) << std::endl;
}