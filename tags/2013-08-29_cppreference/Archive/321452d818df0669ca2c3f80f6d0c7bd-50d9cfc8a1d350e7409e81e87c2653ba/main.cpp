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
        return f(std::move(t), fold(r, f, *std::move(val)));
    return t;
}

template<typename R, typename F> auto filter(R r, F f) {
    return [=]() -> decltype(r()) {
        while(auto val = r()) {
            if (f(*val)) return std::move(val);
        }
        return std::nullopt;
    };
}

template<typename R, typename F> auto map(R r, F f) {
    return [=]() -> std::optional<decltype(f(*r()))> {
        if(auto val = r()) return f(*std::move(val));
        return std::nullopt;        
    };
}

template<typename R1, typename T2> auto concat(R1 r1, R2 r2) {
    bool first = true;
    return [=] mutable {
        if (first) {
            auto val = r1();
            if (val) return val;
            first = false;
        }
        return r2();
    };
}