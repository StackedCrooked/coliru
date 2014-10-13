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

// let's test: functions for int and string
void f_int(int x){std::cout<<"int "<<x<<std::endl;}

template<typename T>
void f_string(const T& x){std::cout<<"string "<<x<<std::endl;}

// let's use static_if
template<typename T>
void check(const T& t)
{
    static_if( std::is_same<T,int>() )([&](auto){
        f_int(t);
    })
    .else_if( std::is_constructible<std::string,const T&>() )([&](auto){
        f_string(t);
    })
    .else_([&](auto){
        std::cout<<"no idea: "<<t<<std::endl;
    })
    ;
}


int main()
{
    std::cout<<"1:   "; check(1);
    std::cout<<"sss: "; check("sss");
    std::cout<<"1.1: "; check(1.1);
}