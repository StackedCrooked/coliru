#include <tuple>

template <std::size_t...> 
struct indices_list {};
template <std::size_t N, std::size_t... I>
struct indices : public indices<N-1, N-1, I...> { const static std::size_t value = N; };
template <std::size_t... I>
struct indices<0, I...> : public indices_list<I...>{ const static std::size_t value = 0; };

template <> 
struct special_flatten { /* Tits. */ };

template <std::size_t n, typename... Tn>
struct flatten { typedef void type; typedef std::tuple<> tuple_type; };

template <typename T, typename... Tn>
struct flatten<0, T, Tn...> { typedef T type; typedef std::tuple<T, flatten<Tn>::type...> tuple_type; };

template <std::size_t n,typename T, typename... Tn>
struct flatten<n, T, Tn...> : special_flatten<indices<n>, T, Tn...> { typedef T type; typedef std::tuple<decltype( std::get</*This is helpful.*/>( T ) )..., flatten<Tn>::type...> tuple_type; };

template <typename... Tn>
struct std_get_type_list {
    typedef flatten<Tn...>::tuple_type type;
};

template <typename... Tn>
auto tuple_cat( Tn&&... meow ) {
    typedef std_get_type_list<Tn...>::tuple_type purr;
    // We'll do the actualy expansion after we figure out the top...
    return purr(  );
}

int main() {
    
    std::tuple<int, float, double> meow;
    long long arf;
    std::pair<unsigned, unsigned long long> woof;
    
    struct make_error {} = tuple_cat( meow, arf, woof );
}