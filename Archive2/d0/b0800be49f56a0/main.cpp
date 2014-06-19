#include <iostream>
#include <functional>
#include <memory>
#include <cxxabi.h>
#include <type_traits>
#include <utility>

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

B b4a (A) {   B b; return b;   }
C c4b (B) {   C c; return c;   }

template <typename F, typename G>
class Composition {
    F f;
    G g;

public:
    template <typename T, typename U>
    Composition(T&& t, U&& u) :
        f(std::forward<T>(t)), g(std::forward<U>(u)) {}
    
    template <typename... Args>
    auto operator () (Args&&... args) -> decltype(f(g(std::forward<Args>(args)...))) {
        return f(g(std::forward<Args>(args)...));
    }
};

template <typename F, typename G>
inline Composition<typename std::decay<F>::type, typename std::decay<G>::type>
composition(F&& f, G&& g)
{   
    return {std::forward<F>(f), std::forward<G>(g)};
}

int main()
{
    cout << "b4a : " << type_name<decltype(b4a)>() << endl;
    cout << "c4b : " << type_name<decltype(c4b)>() << endl;
    auto c4a = composition(c4b, b4a);
    cout << "c4a : " << type_name<decltype(c4a)>() << endl;
    cout << "c4a(A) : " << type_name<decltype(c4a(A{}))>() << endl;

    auto lb4a = [=] (A) { B b; return b; };
    auto lc4b = [=] (B) { C c; return c; };
    auto lc4a = composition(lc4b, lb4a);
    cout << "lc4a : " << type_name<decltype(lc4a)>() << endl;
    cout << "lc4a(A) : " << type_name<decltype(lc4a(A{}))>() << endl;
}
