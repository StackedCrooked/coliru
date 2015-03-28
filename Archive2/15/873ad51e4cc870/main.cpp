#include <utility>
#include <cstddef>
#include <type_traits>
#include <iostream>
#include <tuple>
#define show(variable) std::cout << #variable << " = " << variable << std::endl;

template<class...> struct type_list {};

// Given a list of types List, a number N, and a type T, count the number of times T appears in the first N types of List.
template<std::size_t N, class T, class List, std::size_t V = 0> 
struct count_in_first_N;

template<std::size_t N, class T, std::size_t V, class Head, class... Tail> 
struct count_in_first_N<N, T, type_list<Head, Tail...>, V> : count_in_first_N<N-1, T, type_list<Tail...>, V> { };

template<std::size_t N, class T, std::size_t V, class... Tail> 
struct count_in_first_N<N, T, type_list<T, Tail...>, V> : count_in_first_N<N-1, T, type_list<Tail...>, V+1> { };

template<class T, std::size_t V, class... Tail> 
struct count_in_first_N<0, T, type_list<T, Tail...>, V> : std::integral_constant<std::size_t, V> { };

template<class T, std::size_t V, class Head, class... Tail> 
struct count_in_first_N<0, T, type_list<Head, Tail...>, V> : std::integral_constant<std::size_t, V> { };


// Given a list of types List, produce a list of number Ns, where Ns[i] is the number of times List[i] has appeared in the first i items in List
template<class List, class Seq>
struct generate_counts;

template<class... Ts, std::size_t... Is>
struct generate_counts<type_list<Ts...>, std::index_sequence<Is...>> : std::index_sequence<count_in_first_N<Is, Ts, type_list<Ts...>>::value...> {};

template<class... Ts>
using do_generate_counts = generate_counts<type_list<Ts...>, std::index_sequence_for<Ts...>>;

// Given a list of types List, a 0-based number N, and a type T, determine the index of the Nth T in List
template<std::size_t N, class T, class List, std::size_t V = 0>
struct get_index_in_list;

template<std::size_t N, class T, std::size_t V, class Head, class... Tail>
struct get_index_in_list<N, T, type_list<Head, Tail...>, V> : get_index_in_list<N, T, type_list<Tail...>, V + 1> {};

template<std::size_t N, class T, std::size_t V, class... Tail>
struct get_index_in_list<N, T, type_list<T, Tail...>, V> : get_index_in_list<N-1, T, type_list<Tail...>, V + 1> {};

template<class T, std::size_t V, class... Tail>
struct get_index_in_list<0, T, type_list<T, Tail...>, V> : std::integral_constant<std::size_t, V> {};

template <typename... Ts, typename... Types, std::size_t... Counts>
void tiePackToTuple (const std::tuple<Ts...>& tuple, std::index_sequence<Counts...>, Types&... types) {
    (void) std::initializer_list<int>{ (types = std::get<get_index_in_list<Counts, Types, type_list<Ts...>>::value>(tuple), void(), 0)...};
}

template <typename... Ts, typename... Types>
void tiePackToTuple (const std::tuple<Ts...>& tuple, Types&... types) {
    tiePackToTuple(tuple, do_generate_counts<Types...>(), types...);
}

int main() {
    std::tuple<int, char, double> tuple1 = std::make_tuple(5, '?', 3.14);
    int a;  char c;  double d;
    tiePackToTuple (tuple1, d,a,c);
    show(a)  show(c)  show(d)  // a = 5, c = '?', d = 3.14

    std::cout << '\n';
    int a_, b_;  char c_;  double d_;
    std::tuple<int, char, int, double> tuple2 = std::make_tuple(5, '?', 8, 3.14);
    tiePackToTuple (tuple2, d_, a_, c_, b_);
    show(a_)  show(b_)  show(c_)  show(d_)  // Incorrect (a_ = 8, b_ = gibberish).
     // Should be a_ = 5, b_ = 8.
}