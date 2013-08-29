template<class... Ts> struct list{ using type = list; };

template<unsigned... Is> struct seq{
  using type = seq;
  static constexpr unsigned size = sizeof...(Is);
};

template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<unsigned N, unsigned I, class = typename gen_seq<N>::type>
struct rep;
template<unsigned N, unsigned I, unsigned... Is>
struct rep<N, I, seq<Is...>> : seq<(Is, I)...>{};
template<unsigned N, unsigned I>
using Rep = typename rep<N, I>::type;

template<class S1, class S2>
struct zip;
template<unsigned... I1, unsigned... I2>
struct zip<seq<I1...>, seq<I2...>> : list<seq<I1, I2>...>{};
template<class S1, class S2>
using Zip = typename zip<S1, S2>::type;

template<class L1, class... LRest>
struct concat : L1{};
template<class... T1s, class... T2s, class... LRest>
struct concat<list<T1s...>, list<T2s...>, LRest...>
  : concat<list<T1s..., T2s...>, LRest...>::type{};

template<class S1, class S2>
struct cross;
template<unsigned... I1, class S2>
struct cross<seq<I1...>, S2>
  : concat<Zip<Rep<S2::size, I1>, S2>...>::type{};

int main(){
    struct{}_ = cross<seq<1,2,3>, seq<4,5,6,7>>::type{};
}