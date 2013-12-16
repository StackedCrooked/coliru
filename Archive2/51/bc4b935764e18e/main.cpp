#include <tuple>

template<class...> struct list{};
template<unsigned...> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is> struct gen_seq<0, Is...> : seq<Is...>{};
template<class T> struct gen_seq_for : gen_seq<std::tuple_size<T>::value>{};

template<class Seqs, class T>
T tuple_cat_(Seqs, T t){ return t; }

template<class T, class U, class... Ts, unsigned... Is, unsigned... Js, class... Seqs>
auto tuple_cat_(list<seq<Is...>, seq<Js...>, Seqs...>, T t, U u, Ts... ts)
    -> decltype(tuple_cat_(list<seq<Is..., (Js+sizeof...(Is))...>, Seqs...>(), std::make_tuple(std::get<Is>(t)..., std::get<Js>(u)...), ts...))
{
    return tuple_cat_(list<seq<Is..., (Js+sizeof...(Is))...>, Seqs...>(), std::make_tuple(std::get<Is>(t)..., std::get<Js>(u)...), ts...);
}

template<class... Ts>
auto my_tuple_cat(Ts... ts)
    -> decltype(tuple_cat_(list<typename gen_seq_for<Ts>::type...>(), ts...))
{
    return tuple_cat_(list<typename gen_seq_for<Ts>::type...>(), ts...);
}

int main(){
    std::tuple<int, float, double> t1;
    std::tuple<bool, char, short> t2;
    std::tuple<int*, float*, double*> t3;
    struct{} _ = my_tuple_cat(t1, t2, t3);
}