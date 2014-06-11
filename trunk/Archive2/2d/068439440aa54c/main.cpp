#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/phoenix.hpp>

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

/////////////////////////////////////////////////////
// demonstration:
#include <iostream>
#include <string>

void foo(const char* v) { std::cout << __FUNCTION__ << ": " << v << "\n"; }
void bar(std::string v) { std::cout << __FUNCTION__ << ": " << v << "\n"; }

struct poly_functor {
    template <typename... T>
        void operator()(T&...) const { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

#include <vector>
#include <boost/range/algorithm.hpp>

int main()
{
    poly_functor pf;

    apply_all(&foo, &bar, pf)("fixed invocation is boring");

    auto combined = apply_all(&foo, &bar, pf);

    boost::for_each(
            std::vector<const char*> {"hello", "world", "from", "various"},
            combined);

    struct /*anonymous*/ { int x, y; } point;

    // the variadic case
    apply_all(pf)("bye", 3.14, point);
}
