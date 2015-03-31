#include <iostream>
#include <tuple>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

template<class T>
struct TupleComparable
{
    friend bool operator==(const T& lhs, const T& rhs) {
        return lhs.toTuple() == rhs.toTuple();
    }
};

template <typename F, typename Tuple>
struct Op{
    F& f;
    Tuple& tuple;
    template <typename Index>
    void operator()(Index){
        f(std::get<Index::value>(tuple));
    }
};

template <typename F, typename T>
F for_each(T& obj){
    F f{};
    auto tuple = obj.toTuple();
    boost::mpl::for_each< boost::mpl::range_c<size_t,0,std::tuple_size<decltype(tuple)>::value> >( Op<F, decltype(tuple)>{f, tuple} );
    return std::move(f);
}

struct Foo : private TupleComparable<Foo>
{
    Foo(int a, int b) : a{a}, b{b} {}

    using Tuple = std::tuple<const int&, const int&>;
    
    Tuple toTuple() const {
        return std::tie(a, b);
    }

    int a;
    int b;
};

struct Printer{
    template< typename U > void operator()(U x)
    {
        std::cout << x << ' ';
    }
};

int main(void)
{
    auto f = Foo{10,20};
    auto g = Foo{10,21};
    auto h = Foo{11,20};
    
    std::cout << (f == f) << std::endl;
    std::cout << (f == g) << std::endl;
    std::cout << (f == h) << std::endl;
    
    for_each<Printer>(f);
}