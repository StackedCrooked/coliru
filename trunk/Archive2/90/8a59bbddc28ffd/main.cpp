#define BOOST_RESULT_OF_USE_DECLTYPE
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/phoenix.hpp>
#include <iostream>

void foo(const char* sz) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

void bar(std::string s) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

struct poly_functor {
    template <typename... T>
        void operator()(T&...) const { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

template <typename... F> void RUN(F&&... f) {
    namespace phx = boost::phoenix;
    using namespace phx::arg_names;

    boost::fusion::for_each(
            std::make_tuple(std::forward<F>(f)...),
            phx::bind(arg1, phx::cref("hello"))
        );
}

int main()
{
    RUN(foo, bar, poly_functor());
}
