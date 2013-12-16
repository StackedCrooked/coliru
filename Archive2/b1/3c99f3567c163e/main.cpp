namespace std {
    template <class T = void> struct plus;
    template <class T = void> struct minus;
    template <class T = void> struct multiplies;
    template <class T = void> struct divides;
    template <class T = void> struct modulus;
    template <class T = void> struct negate;
    template <class T = void> struct equal_to;
    template <class T = void> struct not_equal_to;
    template <class T = void> struct greater;
    template <class T = void> struct less;
    template <class T = void> struct greater_equal;
    template <class T = void> struct less_equal;
    template <class T = void> struct logical_and;
    template <class T = void> struct logical_or;
    template <class T = void> struct logical_not;
    template <class T = void> struct bit_and;
    template <class T = void> struct bit_or;
    template <class T = void> struct bit_xor;

    // We don't need to declare bit_not here, as it's new.

    // We don't need to declare the <void> explicit specializations here, as
    // nothing in the C++11 Standard Library will attempt to instantiate them.
}

#include <functional>
#include <utility>

namespace std {
    template <> struct plus<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) + std::forward<U>(u))
           { return std::forward<T>(t) + std::forward<U>(u); }
    };

    template <> struct minus<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) - std::forward<U>(u))
           { return std::forward<T>(t) - std::forward<U>(u); }
    };

    template <> struct multiplies<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) * std::forward<U>(u))
           { return std::forward<T>(t) * std::forward<U>(u); }
    };

    template <> struct divides<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) / std::forward<U>(u))
           { return std::forward<T>(t) / std::forward<U>(u); }
    };

    template <> struct modulus<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) % std::forward<U>(u))
           { return std::forward<T>(t) % std::forward<U>(u); }
    };

    template <> struct negate<void> {
      template <class T> auto operator()(T&& t) const
        -> decltype(-std::forward<T>(t))
           { return -std::forward<T>(t); }
    };

    template <> struct equal_to<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) == std::forward<U>(u))
           { return std::forward<T>(t) == std::forward<U>(u); }
    };

    template <> struct not_equal_to<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) != std::forward<U>(u))
           { return std::forward<T>(t) != std::forward<U>(u); }
    };

    template <> struct greater<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) > std::forward<U>(u))
           { return std::forward<T>(t) > std::forward<U>(u); }
    };

    template <> struct less<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) < std::forward<U>(u))
           { return std::forward<T>(t) < std::forward<U>(u); }
    };

    template <> struct greater_equal<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) >= std::forward<U>(u))
           { return std::forward<T>(t) >= std::forward<U>(u); }
    };

    template <> struct less_equal<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) <= std::forward<U>(u))
           { return std::forward<T>(t) <= std::forward<U>(u); }
    };

    template <> struct logical_and<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) && std::forward<U>(u))
           { return std::forward<T>(t) && std::forward<U>(u); }
    };

    template <> struct logical_or<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) || std::forward<U>(u))
           { return std::forward<T>(t) || std::forward<U>(u); }
    };

    template <> struct logical_not<void> {
      template <class T> auto operator()(T&& t) const
        -> decltype(!std::forward<T>(t))
           { return !std::forward<T>(t); }
    };

    template <class T = void> struct bit_not {
      T operator()(const T& x) const { return ~x; }
      typedef T argument_type;
      typedef T result_type;
    };

    template <> struct bit_and<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) & std::forward<U>(u))
           { return std::forward<T>(t) & std::forward<U>(u); }
    };

    template <> struct bit_or<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) | std::forward<U>(u))
           { return std::forward<T>(t) | std::forward<U>(u); }
    };

    template <> struct bit_xor<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) ^ std::forward<U>(u))
           { return std::forward<T>(t) ^ std::forward<U>(u); }
    };

    template <> struct bit_not<void> {
      template <class T> auto operator()(T&& t) const
        -> decltype(~std::forward<T>(t))
           { return ~std::forward<T>(t); }
    };
}


#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<const char *> v;
    v.push_back("cute");
    v.push_back("fluffy");
    v.push_back("kittens");

    set<string, greater<>> s;
    s.insert("HUNGRY");
    s.insert("EVIL");
    s.insert("ZOMBIES");

    vector<string> dest;

    transform(v.begin(), v.end(), s.begin(), back_inserter(dest), plus<>());

    for (const auto& elem : dest) {
        cout << elem << endl;
    }
}