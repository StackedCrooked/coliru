template<class> struct empty{};

template<class F>
struct overloaded_base{
    F f;
    
    //template<class T>
    using T = int;
    auto operator()(T v) -> decltype(f(v)){ return f(v); }
};

template<class F>
struct overloaded : overloaded_base<F>{
    
    overloaded(F f)
      : overloaded_base<F>{f} {}
    
    using overloaded_base<F>::operator();
      
    template<class T, class = typename empty<T>::type>
    void operator()(T){}
};

template<class F>
overloaded<F> overload(F f){ return {f}; }

void f(int){}

int main()
{
    overload(f)(42);
}
