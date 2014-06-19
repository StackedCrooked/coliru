#include <iostream>
#include <functional>
#include <memory>
#include <cxxabi.h>
#include <tuple>
#include <type_traits>
#include <utility>

template <class T> std::string
type_name()
{   typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
        (   abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr)
        ,   std::free
        );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

struct A { };
struct B { };
struct C { };
struct D { };

B b4a (A) { return {}; }
C c4b (B) { return {}; }
D d4c (C) { return {}; }

template <typename...>
class Composition {
    // This "base case" is only used for zero-function compositions.
public:
    void operator () () {}
};

template <typename F, typename... Remainder>
class Composition<F, Remainder...> : private Composition<Remainder...> {
    // This specialization matches all non-zero function compositions.
    using base_t = Composition<Remainder...>;

    F f_;

    // Use tag dispatching to determine if F is the last function in
    // the composition, and should be called with the args, or
    // if there are further functions and f should be called with
    // the result of passing the args on to the other functions.
    using is_last = std::integral_constant<bool, sizeof...(Remainder) == 0>;
    template <typename... Args>
    auto dispatch(std::true_type, Args&&... args) ->
      decltype(f_(std::forward<Args>(args)...)) {
        return f_(std::forward<Args>(args)...);
    }
    template <typename... Args>
    auto dispatch(std::false_type, Args&&... args) ->
      decltype(f_(static_cast<base_t&>(*this)(std::forward<Args>(args)...))) {
        return f_(static_cast<base_t&>(*this)(std::forward<Args>(args)...));
    }

public:
    template <typename T, typename... Args>
    Composition(T&& t, Args&&... args) :
        base_t(std::forward<Args>(args)...),
        f_(std::forward<T>(t)) {}
    
    template <typename... Args>
    auto operator () (Args&&... args) ->
      decltype(this->dispatch(is_last{}, std::forward<Args>(args)...)) {
        return this->dispatch(is_last{}, std::forward<Args>(args)...);
    }
};

template <typename... Functions>
inline Composition<typename std::decay<Functions>::type...>
composition(Functions&&... f)
{   
    return {std::forward<Functions>(f)...};
}

int main()
{
    using namespace std;

    cout << "b4a : " << type_name<decltype(b4a)>() << endl;
    cout << "c4b : " << type_name<decltype(c4b)>() << endl;
    auto c4a = composition(c4b, b4a);
    cout << "c4a : " << type_name<decltype(c4a)>() << endl;
    cout << "c4a(A) : " << type_name<decltype(c4a(A{}))>() << endl;
    c4a(A{});

    auto lb4a = [=] (A) { B b; return b; };
    auto lc4b = [=] (B) { C c; return c; };
    auto lc4a = composition(lc4b, lb4a);
    cout << "lc4a : " << type_name<decltype(lc4a)>() << endl;
    cout << "lc4a(A) : " << type_name<decltype(lc4a(A{}))>() << endl;
    lc4a(A{});

    auto d4a = composition(d4c, c4b, b4a);
    cout << "d4a : " << type_name<decltype(d4a)>() << endl;
    cout << "d4a(A) : " << type_name<decltype(d4a(A{}))>() << endl;
    d4a(A{});
    
    auto empty = composition();
    cout << "empty : " << type_name<decltype(empty)>() << endl;
    cout << "empty() : " << type_name<decltype(empty())>() << endl;
    empty();
}
