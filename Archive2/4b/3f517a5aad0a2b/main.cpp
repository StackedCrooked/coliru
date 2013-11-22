template<class R>
struct caller{
    R _value;
    template<class F, class... Args>
    caller(F f, Args&&... args)
        : _value(f(std::forward<Args>(args)...)) {}
        
    R&& value() &&{ return std::move(_value); }
};

template<>
struct caller<void>{
    template<class F, class... Args>
    caller(F f, Args&&... args)
    { f(std::forward<Args>(args)...); }
    
    void value() &&{}
};