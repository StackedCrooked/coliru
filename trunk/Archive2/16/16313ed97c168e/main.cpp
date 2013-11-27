#include <tuple>

template <std::size_t...> 
struct indices_list {};
template <std::size_t N, std::size_t... I>
struct indices : public indices<N-1, N-1, I...> { const static std::size_t value = N; };
template <std::size_t... I>
struct indices<0, I...> : public indices_list<I...>{ const static std::size_t value = 0; };
template <typename... Tn>
struct type_list : public indices_list<sizeof...( Tn )>{ };

template <std::size_t... I, typename... Tn>
auto true_tuple_cat( indices<I...>, Tn&&... meow ) {
    return std::get<I>( meow );
}

template <typename... Tn>
auto tuple_cat( Tn&&... meow ) {
    return true_tuple_cat( type_list<Tn...>, std::forward<Tn>( meow )... ) ;
}

int main() {
    
    std::tuple<int, float, double> kitty;
    long long doggy;
    std::pair<unsigned, unsigned long long> cat;
    
    struct make_error {} = tuple_cat( kitty, std::tie( doggy ), cat );
}