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
function<R (T)> compose 
(   std::function <R (S)> r4s
,   std::function <S (T)> s4t   ) 
{   return [=] (T t) {   r4s (s4t (t));  };  }

int main()
{
    cout << "b4a : " << type_name<decltype(b4a)>() << endl;
    cout << "c4b : " << type_name<decltype(c4b)>() << endl;
    auto c4a = [=] (A a) { return c4b (b4a (a)); };
//    auto c4a = compose (c4b, b4a);
    cout << "c4a : " << type_name<decltype(c4a)>() << endl;
//    auto la2b = [=] (A a) { B b; return b; };
//    auto lb2c = [=] (B b) { C c; return c; };
//    cout << "\\.a -> b : " << type_name<decltype(la2b)>() << endl;
//    cout << "\\.b -> c : " << type_name<decltype(lb2c)>() << endl;
//    auto la2c = compose (lb2c, la2b);
//    cout << "\\.a  -> c : " << type_name<decltype(la2c)>() << endl;
}
