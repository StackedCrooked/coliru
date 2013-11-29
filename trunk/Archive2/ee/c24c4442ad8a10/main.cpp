#include <tuple>

template<unsigned, unsigned> struct ix{};

template<class...> struct list{};

template<class Ixs, unsigned AccX, unsigned AccY, unsigned... Sizes>

struct gen_ixs : Ixs{};

template<class... Ixs, unsigned AccX, unsigned AccY, unsigned... Sizes>
struct gen_ixs<list<Ixs...>, AccX, AccY, AccY, Sizes...>
    : gen_ixs<list<Ixs...>, AccX+1, 0, Sizes...>{};
    
template<class... Ixs, unsigned AccX, unsigned AccY, unsigned N, unsigned... Sizes>
struct gen_ixs<list<Ixs...>, AccX, AccY, N, Sizes...>
    : gen_ixs<list<Ixs..., ix<AccX, AccY>>, AccX, AccY + 1, N, Sizes...>{};

template<unsigned... Xs, unsigned... Ys, class Tuples>
auto tuple_cat_(list<ix<Xs, Ys>...>, Tuples ts)
    -> decltype(std::make_tuple(std::get<Ys>(std::get<Xs>(ts))...))
{ return std::make_tuple(std::get<Ys>(std::get<Xs>(ts))...); }

template<class... Ts>
auto my_tuple_cat(Ts... ts)
    -> decltype(tuple_cat_(gen_ixs<list<>, 0, 0, std::tuple_size<Ts>::value...>(), std::make_tuple(ts...)))
{ return tuple_cat_(gen_ixs<list<>, 0, 0, std::tuple_size<Ts>::value...>(), std::make_tuple(ts...)); }

int main(){
    std::tuple<int, float, double> t1;
    std::tuple<bool, char> t2;
    std::tuple<int*, float*, double*, void*> t3;
    struct{} _ = my_tuple_cat(t1, t2, t3);
}