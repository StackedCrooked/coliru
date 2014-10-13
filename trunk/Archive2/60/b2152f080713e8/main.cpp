#include <type_traits>
#include <iostream>
#include <string>

struct noop{
    template<class F> noop operator*(const F& f) const { return noop{}; }
};

struct yes{
    template<class F> noop operator*(const F& f) const { f(0); return noop{}; }
};

struct no{
    yes operator*(yes) const { return yes{}; }
    template<class F> no operator*(const F& f) const { return no{}; }
};

yes static_if(std::true_type){ return yes{}; }
no  static_if(std::false_type){ return no{}; }

#define IF(...)  static_if( __VA_ARGS__ () ) * [&](auto)
#define ELSE_IF(...) * static_if(__VA_ARGS__ () ) * [&](auto)
#define ELSE * yes{} * [&](auto)

// let's test: functions for int and string
void f_int(int x){std::cout<<"int "<<x<<std::endl;}

template<typename T>
void f_string(const T& x){std::cout<<"string "<<x<<std::endl;}

// let's use static_if
template<typename T>
void check(const T& t)
{
    IF( std::is_same<T, int> )
    {
        f_int(t);
    }
    ELSE_IF( std::is_constructible<std::string, const T&> )
    {
        f_string(t);
    }
    ELSE
    {
        std::cout<<"no idea: "<<t<<std::endl;
    };
}

int main()
{
    std::cout<<"1:   "; check(1);
    std::cout<<"sss: "; check("sss");
    std::cout<<"1.1: "; check(1.1);
}