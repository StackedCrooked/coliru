#include <boost/function.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/any_range.hpp>
#include <boost/range/join.hpp>
#include <boost/iterator/function_input_iterator.hpp>

using namespace boost::adaptors;

#include <iostream>
#include <fstream>
#include <vector>

/////////////////////////////////////////////
// multi_join utility
namespace detail {
    struct multi_join_dispatch {
        template <typename R1> static R1 call(R1&& r1) 
            { return std::forward<R1>(r1); }

        template <typename R1, typename... Rs> static auto call(R1&& r1, Rs&&... ranges) 
            -> decltype(boost::range::join(std::forward<R1>(r1), call(std::forward<Rs>(ranges)...)))
            { return boost::range::join(std::forward<R1>(r1), call(std::forward<Rs>(ranges)...)); }
    };
}

template <typename... Rs> auto multi_join(Rs&&... ranges) 
    -> decltype(detail::multi_join_dispatch::call(std::forward<Rs>(ranges)...))
    { return detail::multi_join_dispatch::call(std::forward<Rs>(ranges)...); }

/////////////////////////////////////////////
// generate random numbers [0..9]
struct r10gen {
    typedef int result_type;
    int operator()() const { return rand()%10; } 
} static r10gen_;

/////////////////////////////////////////////
// runtime composition of any input ranges
using AnyR = boost::any_range<int const, boost::single_pass_traversal_tag, int>;

template <typename R1, typename R2, typename R3, typename R4>
    AnyR random_compose_input(R1 const& r1, R2 const& r2, R3 const& r3, R4 const& r4) 
{
    int select = rand()%16;
    std::cout << "selected inputs " << std::showbase << std::hex << select << std::dec << "\n";
    switch(select) {
        case  0:
            static int const* dummy = nullptr;
            return boost::make_iterator_range(dummy, dummy);
        case  1: return multi_join(r1            );
        case  2: return multi_join(    r2        );
        case  3: return multi_join(r1, r2        );
        case  4: return multi_join(        r3    );
        case  5: return multi_join(r1,     r3    );
        case  6: return multi_join(    r2, r3    );
        case  7: return multi_join(r1, r2, r3    );
        case  8: return multi_join(            r4);
        case  9: return multi_join(r1,         r4);
        case 10: return multi_join(    r2,     r4);
        case 11: return multi_join(r1, r2,     r4);
        case 12: return multi_join(        r3, r4);
        case 13: return multi_join(r1,     r3, r4);
        case 14: return multi_join(    r2, r3, r4);
        case 15: return multi_join(r1, r2, r3, r4);
    }
    throw "oops";
}

/////////////////////////////////////////////
// random composition of transformation
using Xfrm = boost::function<int(int)>;

template <typename F1, typename F2, typename F3, typename F4>
    Xfrm random_transform(F1 const& f1, F2 const& f2, F3 const& f3, F4 const& f4) 
{
    int select = rand()%16;
    std::cout << "selected transforms " << std::showbase << std::hex << select << std::dec << "\n";
    switch(select) {
        case  0: return [=](int i){ return   (  (  (  (i)))); };
        case  1: return [=](int i){ return   (  (  (f1(i)))); };
        case  2: return [=](int i){ return   (  (f2(  (i)))); };
        case  3: return [=](int i){ return   (  (f2(f1(i)))); };
        case  4: return [=](int i){ return   (f3(  (  (i)))); };
        case  5: return [=](int i){ return   (f3(  (f1(i)))); };
        case  6: return [=](int i){ return   (f3(f2(  (i)))); };
        case  7: return [=](int i){ return   (f3(f2(f1(i)))); };
        case  8: return [=](int i){ return f4(  (  (  (i)))); };
        case  9: return [=](int i){ return f4(  (  (f1(i)))); };
        case 10: return [=](int i){ return f4(  (f2(  (i)))); };
        case 11: return [=](int i){ return f4(  (f2(f1(i)))); };
        case 12: return [=](int i){ return f4(f3(  (  (i)))); };
        case 13: return [=](int i){ return f4(f3(  (f1(i)))); };
        case 14: return [=](int i){ return f4(f3(f2(  (i)))); };
        case 15: return [=](int i){ return f4(f3(f2(f1(i)))); };
    }
    throw "oops";
}

int main(int argc, char const** argv) {
    using InIt = std::istream_iterator<int>;

    if (argc!=4) return 255;
    std::ifstream f1(argv[1]), f2(argv[2]), f3(argv[3]);

    auto r1 = boost::make_iterator_range(InIt(f1), {}),
         r2 = boost::make_iterator_range(InIt(f2), {}),
         r3 = boost::make_iterator_range(InIt(f3), {});

    auto fi_b = boost::make_function_input_iterator(r10gen_, 0);
    auto fi_l = boost::make_function_input_iterator(r10gen_, 10);
    auto r4 = boost::make_iterator_range(fi_b, fi_l);

    srand(time(0));
    for (int i : random_compose_input(r1,r2,r3,r4) 
               | transformed(random_transform(
                    [](int i) { return i/3; },
                    [](int i) { return -4*i; },
                    [](int i) { return 100+i; },
                    [](int i) { return sqrt(abs(i)); }
                 ))
        )
    { 
        std::cout << i << " ";
    }
}
