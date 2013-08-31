template<typename R, typename F> auto fold(R r, F f) 
-> decltype(fold(r, f, *r())) 
{
    if (auto val = r())
        return fold(r, f, *val);
    assert("Fuckbuckets.");    
}
template<typename R, typename F, typename T> auto fold(R r, F f, T t)
-> decltype(fold(r, f, *r()))
{
    if (auto val = r())
        return f(t, fold(r, f, *val));
    return t;
}

template<typename R, typename F> auto filter(R r, F f) {
    return [=]() -> decltype(r()) {
        while(auto val = r()) {
            if (f(*val)) return val;
        }
        return std::nullopt;
    };
}

template<typename R, typename F> auto map(R r, F f) {
    return [=]() -> std::optional<decltype(f(*r()))> {
        if(auto val = r()) return f(*val);
        return std::nullopt;        
    };
}