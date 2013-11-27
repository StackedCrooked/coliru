#include <tuple>

template<unsigned X, unsigned Y> struct ix{ enum{ x = X, y = Y }; };

template<class...> struct list{ using type = list; };
template<class... Ls> struct concat : Ls...{};
template<class... L1, class...L2, class... Ls>
struct concat<list<L1...>, list<L2...>, Ls...> : concat<list<L1..., L2...>, Ls...>{};

template<unsigned... Is> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is> struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is> struct gen_seq<0, Is...> : seq<Is...>{};
template<class T> using GenSeqFor = typename gen_seq<std::tuple_size<T>::value>::type;

template<unsigned X, class Yseq> struct gen_ixs2;
template<unsigned X, unsigned... Ys>
struct gen_ixs2<X, seq<Ys...>> : list<ix<X, Ys>...>{};

template<class S, class... Ts> struct gen_ixs;
template<unsigned... Is, class... Ts>
struct gen_ixs<seq<Is...>, Ts...> : concat<typename gen_ixs2<Is, GenSeqFor<Ts>>::type...>::type{};

template<class... Ixs, class Tuples>
auto tuple_cat_(list<Ixs...>, Tuples ts)
    -> decltype(std::make_tuple(std::get<Ixs::y>(std::get<Ixs::x>(ts))...))
{ return std::make_tuple(std::get<Ixs::y>(std::get<Ixs::x>(ts))...); }

template<class... Ts>
auto my_tuple_cat(Ts... ts)
    -> decltype(tuple_cat_(gen_ixs<typename gen_seq<sizeof...(Ts)>::type, Ts...>(), std::make_tuple(ts...)))
{ return tuple_cat_(gen_ixs<typename gen_seq<sizeof...(Ts)>::type, Ts...>(), std::make_tuple(ts...)); }

int main(){
    std::tuple<int, float, double> t1;
    std::tuple<bool, char> t2;
    std::tuple<int*, float*, double*, void*> t3;
    struct{} _ = my_tuple_cat(t1, t2, t3);
}