#include <iostream>
#include <functional>
#include <memory>
#include <cxxabi.h>
using namespace std;

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

B b4a (A a) {   B b; return b;   }
C c4b (B b) {   C c; return c;   }

template <typename R, typename S, typename T>
function<R (T)> compose1 
(   function <R (S)> r4s
,   function <S (T)> s4t   ) 
{   return [=] (T t) {   return r4s (s4t (t));  };  }

template <typename R, typename S, typename T>
function<R(T)> composition
(   R(r4s)(S)
,   S(s4t)(T)   ) 
{   return [=] (T t) {   return r4s (s4t (t));  };  }

int main()
{
    cout << "b4a : " << type_name<decltype(b4a)>() << endl;
    cout << "c4b : " << type_name<decltype(c4b)>() << endl;
    auto c4a = composition<C, B, A> (c4b, b4a);
    cout << "c4a : " << type_name<decltype(c4a)>() << endl;
    auto lb4a = [=] (A a) { B b; return b; };
    auto lc4b = [=] (B b) { C c; return c; };
    auto lc4a = composition<C, B, A>(lc4b, lb4a);
    cout << "lc4a : " << type_name<decltype(lc4a)>() << endl;
}
