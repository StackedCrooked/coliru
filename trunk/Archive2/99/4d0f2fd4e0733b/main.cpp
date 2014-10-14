#include <iostream>
#include <string>
#include <type_traits>

struct noop{ // do nothing
    template<class F> noop else_(const F& f) const { return noop{}; }
    template<class F> noop else_if(const F& f) const { return noop{}; }
    template<class F> noop operator()(const F& f) const { return noop{}; }
};

struct yes{ // executing first, no dothing for others
    template<class F> noop operator()(const F& f) const { f(0); return noop{}; }
    template<class F> noop else_if(const F& f) const { return noop{}; }
};

struct no{
    template<class F> auto else_(const F& f) const { f(0); }
    yes else_if(std::true_type){ return yes{}; }
    no  else_if(std::false_type){ return no{}; }
    template<class F> no operator()(const F& f) const { return no{}; }
};

yes static_if(std::true_type){ return yes{}; }
no  static_if(std::false_type){ return no{}; }

using namespace std;

template<typename T>
void check(T x)
{
    static_if( is_same<T, string>() )([&](auto){
        x.size(); // COMPILER ERROR on Clang, but ok on GCC
        [](auto z)
        {
            z.size(); // OK
        }(x);
    });
}


int main()
{
    check(1);
    check(""s);
}
