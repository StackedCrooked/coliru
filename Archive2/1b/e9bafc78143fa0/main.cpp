#include <type_traits>

template<class... Args, class R>
void set(R fun_ptr(Args...)){}

template<class Sig>
void set(Sig* fun_ptr){}

template<class... Args, class R, class C>
void set(R (C::*mem_ptr)(Args...)){}

template<class Sig, class C>
void set(Sig C::* mem_ptr){}

template<class T> struct type{};

template<class... Args, class F,
    class = typename std::result_of<F&(Args...)>::type> // SFINAE
void set_i(type<Args...>, F f){}

template<class R, class... Args, class F,
    class E = typename std::result_of<F&(Args...)>::type> // SFINAE
void set_i(type<R(Args...)>, F f){}

template<class Sig, class F>
auto set(F f)
    -> decltype(set_i(type<Sig>{}, f))
{}

void f(int){}
void f(int, int){}

struct X{
    void f(int){}
    void f(int, int){}
};

struct Y{
    void operator()(int){}
    void operator()(int, int){}
};

int main(){
    set<int>(f);
    set<void(int, int)>(f);
    //set<int*>(f); // OR fail
    set<int>(&X::f);
    set<void(int, int)>(&X::f);
    //set<int*>(&X::f); // OR fail
    set<int>(Y{});
    set<void(int, int)>(Y{});
    //set<int*>(Y{}); // OR fail
}