#include <iostream>
#include <memory>
#include <boost/variant.hpp>

namespace visitor_galore // this is my make-shift replacement for typeswitch (I couldn't find it/make it work)
{
    template<typename T, class...Fs> struct visitor_t;

    template<typename T, class F1, class...Fs>
    struct visitor_t<T, F1, Fs...> : F1, visitor_t<T, Fs...>::type {
        typedef visitor_t type;
        visitor_t(F1 head, Fs...tail) : F1(head), visitor_t<T, Fs...>::type(tail...) {}

        using F1::operator();
        using visitor_t<T, Fs...>::type::operator();
    };

    template<typename T, class F> struct visitor_t<T, F> : F, boost::static_visitor<T> {
        typedef visitor_t type;
        visitor_t(F f) : F(f) {}
        using F::operator();
    };

    template<typename T=void, class...Fs>
    typename visitor_t<T, Fs...>::type make_visitor(Fs...x) { return {x...}; }
}

using visitor_galore::make_visitor;
using Human = int;          // just an 
using Zombie = double;      // example

using Humanoid = boost::variant<Human, Zombie>;

const std::string name(Humanoid const& x) {
    return boost::apply_visitor(make_visitor<std::string>(
                    [](Human const&)  { return "Human"; },
                    [](Zombie const&) { return "Zombie"; }
                ), x);
}

int main() {
    Zombie x = 5;
    std::cout << name(x);
    return 0;
}
