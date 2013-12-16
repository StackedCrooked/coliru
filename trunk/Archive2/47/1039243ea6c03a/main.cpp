#include <tuple>

template<unsigned...> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is> struct gen_seq<0, Is...> : seq<Is...>{};
template<class T> struct gen_seq_for : gen_seq<std::tuple_size<T>::value>{};

template<unsigned... Is, unsigned... Js, class T, class U>
auto tuple_cat_(seq<Is...>, seq<Js...>, T t, U u)
    -> decltype(std::make_tuple(std::get<Is>(t)..., std::get<Js>(u)...))
{
    return std::make_tuple(std::get<Is>(t)..., std::get<Js>(u)...);
}

template<unsigned... Is, unsigned... Js, class T, class U, class V, class... Ts>
auto tuple_cat_(seq<Is...>, seq<Js...>, T t, U u, V v, Ts... ts)
    -> decltype(tuple_cat_(seq<Is..., (Js+sizeof...(Is))...>(), gen_seq_for<V>(), std::make_tuple(std::get<Is>(t)..., std::get<Js>(u)...), v, ts...))
{
    return tuple_cat_(seq<Is..., (Js+sizeof...(Is))...>(), gen_seq_for<V>(), std::make_tuple(std::get<Is>(t)..., std::get<Js>(u)...), v, ts...);
}

template<class T, class U, class... Ts>
auto my_tuple_cat(T t, U u, Ts... ts)
    -> decltype(tuple_cat_(gen_seq_for<T>(), gen_seq_for<U>(), t, u, ts...))
{
    return tuple_cat_(gen_seq_for<T>(), gen_seq_for<U>(), t, u, ts...);
}

int main(){
    std::tuple<int, float, double> t1;
    std::tuple<bool, char, short> t2;
    std::tuple<int*, float*, double*> t3;
    struct{} _ = my_tuple_cat(t1, t2, t3);
}