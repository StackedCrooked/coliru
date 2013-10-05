#include <tuple>
#include <type_traits>
#include <stdint.h>

// vvv auxilliary
template<class T>
using Invoke = typename T::type;

template<bool B, class T>
using EnableIfC = Invoke<std::enable_if<B, T>>;

template<bool B, class T, class F>
using IfC = Invoke<std::conditional<B, T, F>>;

template<size_t...> struct seq{ using type = seq; };
template<size_t I, size_t... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};
template<size_t N>
using GenSeq = Invoke<gen_seq<N>>;

template<class..., class T> constexpr T depend(T v){ return v; }
// ^^^ auxilliary

template<class T> struct assigned{ using type = T; T value; };
template<class T> struct missing{ using type = T; };

template<size_t I, class T> struct elem{ T value; };

template<class S, class... Ts>
struct foo_params;

template<size_t... Is, class... Ts>
struct foo_params<seq<Is...>, Ts...> : elem<Is, Ts>...{
    
    foo_params() = default;
    foo_params(foo_params&&) = default;
    
    template<class... Us>
    foo_params(foo_params<seq<Is...>, Us...>&&){
        static_assert(depend<Us...>(false), "missing argument to named parameters");
    }
    
    template<class... Us, EnableIfC<sizeof...(Us) == sizeof...(Ts), int> = 0>
    foo_params(Us&&... us) : elem<Is, Ts>{us}...{}
    
    template<size_t I>
    using Elem = Invoke<std::tuple_element<I, std::tuple<Ts...>>>;
    
    template<size_t I, size_t SI, class T, class U, EnableIfC<I == SI, int> = 0>
    assigned<T> assign(elem<I, missing<T>>&, U&& v){ return {v}; }
    
    template<size_t I, size_t SI, class T, class U, EnableIfC<I != SI, int> = 0>
    T assign(elem<SI, T>& e, U&&){ return e.value; }
    
    template<size_t I>
    using Result = foo_params<seq<Is...>, IfC<I == Is, assigned<Invoke<Elem<I>>>, Elem<Is>>...>;
    
    template<class U>
    Result<0> size(U&& v){ return { assign<0, Is>(*this, v)... }; }
    template<class U>
    Result<1> balance(U&& v){ return { assign<1, Is>(*this, v)... }; }
    template<class U>
    Result<2> flipped(U&& v){ return { assign<2, Is>(*this, v)... }; }
    
    template<size_t I>
    elem<I, Elem<I>>& get(){ return *this; }
    
    Invoke<Elem<0>>& size(){ return get<0>().value.value; }
    Invoke<Elem<1>>& balance(){ return get<1>().value.value; }
    Invoke<Elem<2>>& flipped(){ return get<2>().value.value; }
};

#include <iostream>

template<class... Ts>
using FooParams = foo_params<GenSeq<sizeof...(Ts)>, assigned<Ts>...>;

using FooArgs = foo_params<GenSeq<3>, missing<int>, missing<float>, missing<bool>>;

void foo(FooParams<int, float, bool> p){
    std::cout << p.size() << " " << p.balance() << " " << p.flipped() << "\n";
}

int main(){
    foo(FooArgs{}.flipped(true).size(10));
}