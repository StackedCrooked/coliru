#include <boost/variant.hpp>

class A {};
class B {};
class C {};
class D {};

using v1 = boost::variant<A, B>;
using v2 = boost::variant<C, D>;

namespace detail {
    struct F : boost::static_visitor<int> {
        template <typename... T>
        int operator()(boost::variant<T...> const& v) const {
            return boost::apply_visitor(*this, v);
        }

        int operator()(A) const { return 0; }
        int operator()(B) const { return 0; }
        int operator()(C) const { return 1; }
        int operator()(D) const { return 1; }
    } _f;
}

template <typename T>
int f(T const& t) {
    return detail::F()(t);
}

int main() {
    std::cout <<  f(A{})   << "\n";
    std::cout <<  f(B{})   << "\n";
    std::cout <<  f(C{})   << "\n";
    std::cout <<  f(D{})   << "\n";
    std::cout <<  f(v1{})  << "\n";
    std::cout <<  f(v2{})  << "\n";
}

