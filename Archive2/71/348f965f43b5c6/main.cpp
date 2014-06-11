#define BOOST_RESULT_OF_USE_DECLTYPE
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/phoenix.hpp>
#include <iostream>

void foo(const char*) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

void bar(std::string) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

struct poly_functor {
    template <typename... T>
        void operator()(T&...) const { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

template <typename... T>
void free_poly_function(T&...) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

BOOST_PHOENIX_ADAPT_FUNCTION(void, free_poly3, free_poly_function, 3)

template <typename... F>
struct sequence_application
{
    explicit sequence_application(F... fs) : fs(fs...) { }

    template <typename... Args>
        void operator()(Args const&... args) const {
            namespace phx = boost::phoenix;
            using namespace phx::arg_names;

            boost::fusion::for_each(fs, phx::bind(arg1, phx::cref(args)...));
        }
    private:
        std::tuple<F...> fs;
};

template <typename... F>
sequence_application<F...> apply_all(F&&... fs) {
    return sequence_application<F...>(std::forward<F>(fs)...);
}

int main()
{
    poly_functor pf;

    auto combined = apply_all(&foo, &bar, pf);
    combined("hello");

    struct /*anonymous*/ { int x, y; } point;
    apply_all(pf)("bye", 3.14, point);
}
