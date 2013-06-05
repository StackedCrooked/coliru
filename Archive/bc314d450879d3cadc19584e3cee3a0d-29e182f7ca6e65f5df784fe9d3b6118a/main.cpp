#include <utility>

template<class F>
struct protected_{
    F f;
    
    template<class... Args>
    auto operator()(Args&&... args){
        return f(std::forward<Args>(args)...);
    }
};

template<class F>
protected_<F> protect(F&& f){ return {std::forward<F>(f)}; }

// ***

template<class F, class... Fs>
struct overloaded : F, overloaded<Fs...>{
    using fbase = overloaded<Fs...>;
    
    template<class G, class... Gs>
    overloaded(G&& g, Gs&&... gs)
      : F(std::forward<G>(g)), fbase(std::forward<Gs>(gs)...) {}
        
    using F::operator();
    using fbase::operator();
};

template<class F>
struct overloaded<F> : F{
    template<class G>
    overloaded(G&& g) : F(std::forward<G>(g)) {}
    
    using F::operator();
};

template<class... Fs>
overloaded<Fs...> overload(Fs&&... fs){ return {std::forward<Fs>(fs)...}; }

// ***

template<unsigned I> struct ranking : ranking<I-1>{};
template<> struct ranking<0>{};

template<unsigned I, class F>
struct ranked : F{
    template<class G>
    ranked(G&& g) : F(std::forward<G>(g)) {}
    
    template<class... Args>
    auto operator()(ranking<I>, Args&&... args){
        return F::operator()(std::forward<Args>(args)...);
    }
};

namespace aux{
template<unsigned... Is> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<unsigned I>
using GenSeq = typename gen_seq<I>::type;

template<unsigned I, class F>
struct maybe_ranked{ using type = ranked<I, F>; };
template<unsigned I, unsigned J, class F>
struct maybe_ranked<I, ranked<J, F>>{ using type = ranked<J, F>; };

template<unsigned I, class F>
using MaybeRanked = typename maybe_ranked<I, F>::type;
    
template<class Seq, class... Fs> struct ro_base;
template<unsigned... Is, class... Fs>
struct ro_base<seq<Is...>, Fs...>{ using type = overloaded<MaybeRanked<sizeof...(Fs) - Is, Fs>...>; };
    
template<class... Fs>
using RankedOverloadBase = typename ro_base<GenSeq<sizeof...(Fs)>, Fs...>::type;
} // aux::

template<class... Fs>
struct rank_overloaded : aux::RankedOverloadBase<Fs...>{
    using fbase = aux::RankedOverloadBase<Fs...>;
    using fbase::fbase;
    
    using select_overload = ranking<sizeof...(Fs)>;
    
    template<class... Args>
    auto operator()(Args&&... args){
        return fbase::operator()(select_overload(), std::forward<Args>(args)...);
    }
};

template<class... Fs>
rank_overloaded<Fs...> ranked_overload(Fs&&... fs){ return {std::forward<Fs>(fs)...}; }

// ***

// overload(guard<Conds...>(fs)...) ?

#include <type_traits>

struct X final{
    int operator()(int i){ return i; }
};

int main(){
    auto f = overload([](int i){ return i; }, [](double d){ return d; });
    static_assert(std::is_same<decltype(f(42)), int>(), "f(int)");
    static_assert(std::is_same<decltype(f(13.37)), double>(), "f(double)");
    
    auto rf = ranked_overload([](int){ return 42; }, [](int){ return 13.37; });
    static_assert(std::is_same<decltype(rf(42)), int>(), "rf(int)");
    
    auto ff = overload(protect(X{}), [](double d){ return d; });
    static_assert(std::is_same<decltype(ff(42)), int>(), "ff(int)");
}
