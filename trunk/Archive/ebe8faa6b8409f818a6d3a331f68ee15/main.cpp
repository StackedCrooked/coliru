template<class T, class F, class Arg>
auto fold(T& v, F f, Arg a0)
  -> decltype(f(v, a0))
{
    return f(v, a0);
}

template<class T, class F, class Arg, class... Args>
auto fold(T& v, F f, Arg a0, Args... args)
  -> decltype(fold(f(v, a0), f, args...))
{
    return fold(f(v, a0), f, args...);
}

#include <iostream>

struct X{
    struct apply_single{
        X& operator()(X& x, int i){ return x.single(i); }
    };
    X& single(int i){ std::cout << i << " "; return *this; }
    template<class... Ts>
    X& chain(Ts... ts){
        return fold(*this, apply_single(), ts...);
    }
};

int main(){
    X x;
    x.chain(1,2,3,4);
}