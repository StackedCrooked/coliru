#include <iostream>
#include <tuple>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

template<class T>
struct TupleComparable
{
    bool operator==(const TupleComparable& other) const {
        return static_cast<const T&>(*this).toTuple() == static_cast<const T&>(other).toTuple();
    }
};

template<class T>
struct TupleIterable{
    template <typename F, typename Tuple>
    struct Op{
        F& f;
        Tuple& tuple;
        template <typename Index>
        void operator()(Index){
            f(std::get<Index::value>(tuple));
        }
    };
    
    template <typename F>
    F for_each(){
        F f{};
        auto tuple = static_cast<const T&>(*this).toTuple();
        boost::mpl::for_each< boost::mpl::range_c<size_t,0,std::tuple_size<decltype(tuple)>::value> >( Op<F, decltype(tuple)>{f, tuple} );
        return std::move(f);
    }
};

struct Foo : public TupleComparable<Foo>, public TupleIterable<Foo>
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
    
    f.for_each<Printer>();
}