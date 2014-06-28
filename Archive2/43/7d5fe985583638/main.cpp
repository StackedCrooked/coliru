#include <type_traits>
#include </Archive2/36/25776e1939b198/main.cpp>

template<class... Args, class F,
    class = typename std::result_of<F&(Args...)>::type> // SFINAE
void set_i(types<Args...>, F f){}

template<class R, class... Args, class F,
    class E = typename std::result_of<F&(Args...)>::type> // SFINAE
void set_i(types<R(Args...)>, F f){}

template<class F> // typeless
auto set_i(types<>, F f)
->decltype(set_i(function_args_t<decltype(&F::operator())>{}, f)) {
    return set_i(function_args_t<decltype(&F::operator())>{}, f);
}

template<class... Args, class R>
void set(R fun_ptr(Args...)){}

template<class Sig>
void set(Sig* fun_ptr){}

template<class... Args, class R, class C>
void set(R (C::*mem_ptr)(Args...)){}

template<class Sig, class C>
void set(Sig C::* mem_ptr){}

template<class... Sig, class F>
auto set(F f)
    -> decltype(set_i(types<Sig...>{}, f))
{}

void g(int){}
struct Z {
    void g(int){}
};
struct W {
    void operator()(int){}
};

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
    // Magic!
    set(g);
    set(&Z::g);
    set(W{});
    
    set<int>(g);
    set<int>(f);
    set<int, int>(f);
    set<void(int, int)>(f);
    //set<int*>(f); // OR fail
    set<int>(&X::f);
    set<int, int>(&X::f);
    set<void(int, int)>(&X::f);
    //set<int*>(&X::f); // OR fail
    set<int>(Y{});
    set<int, int>(Y{});
    set<void(int, int)>(Y{});
    //set<int*>(Y{}); // OR fail
}