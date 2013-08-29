#include <iostream>
#include <utility>

struct disambiguator_t {};
const auto split = disambiguator_t();

template <typename ...Tn>
void Print ( Tn&&... argn ) {
    using swallow = int[];
    (void)swallow{ (std::cout << argn << " ", 0)... };
}

#include <type_traits>

template<class T>
using Invoke = typename T::type;

template<class C, class T = int>
using DisableIf = Invoke<std::enable_if<!C::value, T>>;

template<class... Ts, class... Vs>
void cleave1(Ts&&... ts, disambiguator_t const&, Vs&&... vs){
    Print( std::forward<Ts>( ts )... );
    
    std::cout << std::endl << "Split!" << std::endl;
    
    Print( std::forward<Vs>( vs )... );
}

template<class... Ts, class U, class... Vs, DisableIf<std::is_same<U, disambiguator_t const&>> = 0>
void cleave1(Ts&&... ts, U&& u, Vs&&... vs){
    cleave1<Ts..., U>(std::forward<Ts>(ts)..., std::forward<U>(u), std::forward<Vs>(vs)...);
}

#include <tuple>

template<class T>
using Unqualified = Invoke<std::remove_cv<Invoke<std::remove_reference<T>>>>;

template<unsigned I, class T>
using TupleElemAt = Invoke<std::tuple_element<I, Unqualified<T>>>;

template<unsigned...> struct seq{ using type = seq; };
template<unsigned I, unsigned Off = 0, unsigned... Is>
struct gen_seq : gen_seq<I-1, Off, I-1, Is...>{};
template<unsigned Off, unsigned... Is>
struct gen_seq<0, Off, Is...> : seq<(Is+Off)...>{};

template<class T, unsigned Off = 0>
using SeqFor = Invoke<gen_seq<std::tuple_size<Unqualified<T>>::value, Off>>;

template<class T>
TupleElemAt<0, T> head(T&& t){
    return std::get<0>(std::forward<T>(t));
}

template<class T, unsigned... Is>
std::tuple<TupleElemAt<Is, T>...> tail(T&& t, seq<Is...>){
    return std::forward_as_tuple(std::get<Is>(std::forward<T>(t))...);
}

template<class T, unsigned... Is>
void tuple_print(T&& t, seq<Is...>){
    using swallow = int[];
    (void)swallow{(std::cout << std::get<Is>(t) << " ", 0)...};
}

template<class T1, class T2>
void cleave2(T1&& t1, disambiguator_t const&, T2&& t2){
    tuple_print(t1, SeqFor<T1>());
    std::cout << "\n" << "split!" << "\n";
    tuple_print(t2, SeqFor<T2>());
}

template<class T1, class U, class T2, DisableIf<std::is_same<U, disambiguator_t const&>> = 0>
void cleave2(T1&& t1, U&& u, T2&& t2)
{
    cleave2(std::tuple_cat(std::forward<T1>(t1), std::forward_as_tuple(std::forward<U>(u))),
            head(std::forward<T2>(t2)), tail(std::forward<T2>(t2), gen_seq<std::tuple_size<Unqualified<T2>>::value-1, 1>()));
}

template<class T, class... Ts>
void cleave2(T&& v, Ts&&... vs){
    cleave2(std::make_tuple(), std::forward<T>(v), std::forward_as_tuple(std::forward<Ts>(vs)...));
}

int main ( int argc, char** argv ) {
    cleave2( 1, 2, 3, split, 4, 5, 6 );
}