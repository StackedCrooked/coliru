template<class F, class... Fs>
struct overloaded{
    F f;
    
    template<class T>
    auto operator()(T v) -> decltype(f(v)){ return f(v); }
};

template<class F, class Fx, class... Fs>
struct overloaded<F, Fx, Fs...> : overloaded<Fx, Fs...>{
    F f;
    
    overloaded(F f_, Fx fx, Fs... fs)
      : overloaded<Fx, Fs...>{fx, fs...}
      , f(f_) {}
      
    using overloaded<Fx, Fs...>::operator();
    
    template<class T>
    auto operator()(T v) -> decltype(f(v)){ return f(v); }
};

template<class... Fs>
overloaded<Fs...> overload(Fs... fs){ return {fs...}; }

#include <string>

int main()
{
    auto o = overload([](int){}, [](std::string){});
    
    o(42);
    o("yay");
}
