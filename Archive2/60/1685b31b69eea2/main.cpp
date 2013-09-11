template<class> struct empty{};

template<class F>
struct overloaded_base{
    F f;
    
    template<class T>
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

int main()
{
    overload([](int){})(42);
}
