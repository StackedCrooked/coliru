/*template<typename R, typename F> auto filter(R r, F f) -> std::function<decltype(r())()> {
    return [=]() -> decltype(r()) {
        while(auto val = r()) {
            if (f(*val)) return std::move(val);
        }
        return std::nullopt;
    };
}

template<typename R, typename F> auto map(R r, F f) -> std::function<std::optional<decltype(f(*r()))()> {
    return [=]() -> std::optional<decltype(f(*r()))> {
        if(auto val = r()) return f(*std::move(val));
        return std::nullopt;        
    };
}

template<typename R1, typename T2> auto concat(R1 r1, R2 r2) 
-> decltype(r1()) {
    static_assert(std::is_same<decltype(r1()), decltype(r2())>::value, "R1 and R2 must return the same types");
    
    return [first = true] mutable {
        if (first) {
            if (auto val = r1()) return val;
            first = false;
        }
        return r2();
    };
}*/

namespace impl {
    template<typename F> struct emptyfold { F f; };
    template<typename T, typename F> struct initialfold { F f; T value; };
}
namespace range {    
    template<typename F> emptyfold<F> auto fold(F f) -> emptyfold<F> { return { std::move(f); } }
    template<typename T, typename F> auto fold(F f, T t) -> emptyfold<F, T> { return { std::move(f), std::move(t) } }
    
    
    template<typename R, typename F, typename T> auto operator|(R r, initialfold<F, T> values)
    -> decltype(r | fold(values.f, *std::move(val))) 
    {
        if (auto val = r())
            return f(std::move(values.t), r | fold(values.f, *std::move(val)));
        return std::move(values.t);
    }
    template<typename R, typename F> auto operator|(R r, emptyfold<F> func)
    -> decltype(r | fold(func.f, *r()))
    {
        if (auto val = r())
            return r | fold(func.f, *std::move(val));
        assert("Fuckbuckets.");
    }
}
int main() {    
    std::cout << [curr = 0] mutable { if (curr < 100) return std::optional<int>(curr++); return std::nullopt; } | range::fold([](int lhs, int rhs) { return lhs + rhs; });
}