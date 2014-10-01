#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>

namespace mytraits {
    template <typename T>
    struct elem_construct { static T call() { return { }; } };
}

namespace detail {
    template <typename... Ts>
        struct internal_fun_helper {
            static typename boost::fusion::vector<Ts...> call() {
                return boost::fusion::vector<Ts...> (std::move(mytraits::elem_construct<Ts>::call())...);
            }
        };

    // helpers that detect the real cardinality of vectors even in the presence of C++03 faux variadics
    // {{{ plumbing
    template <typename FusionVector> struct fun_helper;

    template <typename T1>
        struct fun_helper<boost::fusion::vector<T1> > {
            static typename boost::fusion::vector<T1> call() { return internal_fun_helper<T1>::call(); }
        };

    template <typename T1, typename T2>
        struct fun_helper<boost::fusion::vector<T1,T2> > {
            static typename boost::fusion::vector<T1,T2> call() { return internal_fun_helper<T1,T2>::call(); }
        };

    template <typename T1, typename T2, typename T3>
        struct fun_helper<boost::fusion::vector<T1,T2,T3> > {
            static typename boost::fusion::vector<T1,T2,T3> call() { return internal_fun_helper<T1,T2,T3>::call(); }
        };

    template <typename T1, typename T2, typename T3, typename T4>
        struct fun_helper<boost::fusion::vector<T1,T2,T3,T4> > {
            static typename boost::fusion::vector<T1,T2,T3,T4> call() { return internal_fun_helper<T1,T2,T3,T4>::call(); }
        };

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
        struct fun_helper<boost::fusion::vector<T1,T2,T3,T4,T5> > {
            static typename boost::fusion::vector<T1,T2,T3,T4,T5> call() { return internal_fun_helper<T1,T2,T3,T4,T5>::call(); }
        };

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        struct fun_helper<boost::fusion::vector<T1,T2,T3,T4,T5,T6> > {
            static typename boost::fusion::vector<T1,T2,T3,T4,T5,T6> call() { return internal_fun_helper<T1,T2,T3,T4,T5,T6>::call(); }
        };

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        struct fun_helper<boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7> > {
            static typename boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7> call() { return internal_fun_helper<T1,T2,T3,T4,T5,T6,T7>::call(); }
        };

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        struct fun_helper<boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7,T8> > {
            static typename boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7,T8> call() { return internal_fun_helper<T1,T2,T3,T4,T5,T6,T7,T8>::call(); }
        };

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
        struct fun_helper<boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7,T8,T9> > {
            static typename boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7,T8,T9> call() { return internal_fun_helper<T1,T2,T3,T4,T5,T6,T7,T8,T9>::call(); }
        };

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
        struct fun_helper<boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> > {
            static typename boost::fusion::vector<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> call() { return internal_fun_helper<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>::call(); }
        };
    // }}}
}

template <typename FusionVector> FusionVector fun() {
    return detail::fun_helper<FusionVector>::call();
}

#include <iostream>

// this class is not default constructible
struct  A
{
    A() = delete;
    A(int x) : _i(x) {}
    friend std::ostream& operator<<(std::ostream& os, A const& a) { return os << "A[" << a._i << "]"; }

private:
    int _i;
};

using B = A;
using C = A;

// here's the magic that tells our `fun` factory how to construct A
namespace mytraits {
    template <>
    struct elem_construct<A> { static A call() { return {42}; } };
}

#include <boost/phoenix.hpp>
#include <boost/optional.hpp>
using boost::phoenix::arg_names::arg1;

int main()
{
    namespace fusion = boost::fusion;
    fusion::for_each(fun<fusion::vector<A, B, C>>(), std::cout << arg1 << "\n");
    std::cout << "----\n";
    fusion::for_each(fun<fusion::vector<int, double, std::string, A>>(), std::cout << arg1 << "\n");
    std::cout << "----\n";
    fusion::for_each(fun<fusion::vector<boost::optional<int>>>(), std::cout << arg1 << "\n");
    std::cout << "----\n";
}
