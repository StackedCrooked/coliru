#include <iostream>
#if __cplusplus < 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__) ||  \
    defined(_MSC_VER) && _MSC_VER >= 1600
#define HAS_MOVE_SEMANTICS 1
#elif defined(__clang)
#if __has_feature(cxx_rvalue_references)
#define HAS_MOVE_SEMANTICS 1
#else
#define HAS_MOVE_SEMANTICS 0
#endif
#else
#define HAS_MOVE_SEMANTICS 0
#endif

#if HAS_MOVE_SEMANTICS
#include <algorithm>
namespace _cpp11_detail
{
    template<bool B, class T = void> struct enable_if;
    template<class T> struct enable_if<false, T> { };
    template<class T> struct enable_if<true, T> { typedef T type; };
    template<class T>
    inline char (&is_lvalue(
        T &, typename std::allocator<T>::value_type const volatile &))[2];
    inline char (&is_lvalue(...))[1];
    template<bool LValue, class T>
    inline typename enable_if<!LValue, T>::type move(T v)
    { T r; using std::swap; swap(r, v); return r; }
    template<bool LValue, class T>
    inline typename enable_if<LValue, T>::type move(T &v)
    { T r; using std::swap; swap(r, v); return r; }
    template<bool LValue, class T>
    inline typename enable_if<LValue, T>::type const &move(T const &v)
    { return v; }
}
using _cpp11_detail::move;
namespace std { using _cpp11_detail::move; }
// Define this conditionally, if C++11 is not supported
#define move(...) move<  \
    (sizeof((_cpp11_detail::is_lvalue)((__VA_ARGS__), (__VA_ARGS__))) != 1)  \
>(__VA_ARGS__)
#endif





struct X {
    X() {std::cout << "X()\n";}
    X(X const&) { std::cout << "X(X const&)\n"; }
};

namespace std {
    void swap(X& l, X& r) {
        std::cout << "swap(X&,X&)\n";
    }
}

X test(X v) { return std::move(v); }

int main()
{
    X q;
    int x = 5;
    int y = std::move(x);
    X qq = test(std::move(test(std::move(q))));
}