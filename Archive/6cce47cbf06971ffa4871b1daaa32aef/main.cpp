#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <boost/optional.hpp>

template<class I>
using Maybe = boost::optional<I>;

template<class T>
Maybe<T> Just(T const& v){ return {v}; }

struct Nothing{ 
    operator boost::none_t() const{ return boost::none; }
    template<class T>
    operator Maybe<T>() const{ return boost::none; }
};

template<class T>
using is_nothing = std::is_same<T, Nothing>;

template<class T, class F>
Maybe<T> bind_(Maybe<T> m, F f, std::false_type){
    if(m) return f(*m);
    return boost::none;
}

template<class T, class F>  
Nothing bind_(Maybe<T>, F, std::true_type){ return Nothing{}; }

template<class T, class F>
auto operator|(Maybe<T> m, F f)
    -> decltype(bind_(m, f, is_nothing<decltype(f(*m))>{}))
{
    return bind_(m, f, is_nothing<decltype(f(*m))>{});
}

template<class F>
Nothing operator|(Nothing, F){ return Nothing(); }

template<class T>
std::string show(Maybe<T> const& m) {
    if (m) return "Just " + std::to_string(*m);
    return "Nothing";
}

std::string show(Nothing){ return "Nothing"; }

int main() {
    auto nothing1 = Just(42) | [] (int) { return Nothing(); };
    auto nothing2 = nothing1 | [] (int x) { return Just(x * 2); };
    auto something = Just(3.14) | [] (double x) { return Just(x / 2); } | [] (double y) { return Just(y * 42); };
    std::cout << show(nothing1) << '\n';
    std::cout << show(nothing2) << '\n';
    std::cout << show(something) << '\n';
}
