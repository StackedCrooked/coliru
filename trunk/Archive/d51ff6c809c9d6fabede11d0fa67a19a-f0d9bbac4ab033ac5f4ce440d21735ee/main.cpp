template<unsigned...> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>::type{};

template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<unsigned I, class T>
struct element{ T value; };

template<class Seq, class... Ts> struct tuple_i;

template<unsigned... Is, class... Ts>
struct tuple_i<seq<Is...>, Ts...> : element<Is, Ts>...{
    using base_type = tuple_i;
    
    template<class... Us>
    tuple_i(Us&&... us) : element<Is, Ts>{static_cast<Us&&>(us)}...{}
};

template<class... Ts>
struct tuple : tuple_i<typename gen_seq<sizeof...(Ts)>::type, Ts...>
{
    template<class... Us>
    tuple(Us&&... us) : tuple::base_type(static_cast<Us&&>(us)...){}
    
    template<unsigned I, class T>
    static T& _get(element<I, T>& e){ return e.value; }
};

template<unsigned I, class... Ts>
auto get(tuple<Ts...>& t) -> decltype(t.template _get<I>(t)){ return t.template _get<I>(t); }

#include <type_traits>

int main(){
    tuple<int, bool> t{1,true};
    
    static_assert(std::is_same<int&, decltype(get<0>(t))>(), "0");
    static_assert(std::is_same<bool&, decltype(get<1>(t))>(), "1");
}