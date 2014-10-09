#include <iostream>
#include <list>
#include <tuple>
#include <utility>
#include <cstddef>

struct Base {};
struct A : Base {};  struct B : Base {};  struct C : Base {};
struct D : Base {};  struct E : Base {};  struct F : Base {};

template <int KEY, typename... RANGE> struct Map {};  // one-to-many map (mapping KEY to RANGE...)

template <typename...> struct Data {};

using Database = Data<  Map<0, A,B,C>, Map<1, D,E,F>  >;

template <int N, typename FIRST, typename... REST>
void insertInMenu (std::list<Base*>& menu) {
    menu.push_back(new FIRST);
    insertInMenu<N, REST...> (menu);
}

template <int N>
void insertInMenu (std::list<Base*>&) {}  // End of recursion.

template <typename D, int N>
struct obtainRange;

template <int N, typename... Ts, typename... Maps>
struct obtainRange<Data<Map<N, Ts...>, Maps...>, N>
{
    using type = std::tuple<Ts...>;
};

template <int N, int M, typename... Ts, typename... Maps>
struct obtainRange<Data<Map<M, Ts...>, Maps...>, N> : obtainRange<Data<Maps...>, N> {};

template <int N, typename Tuple, std::size_t... Is>
std::list<Base*> menu(std::index_sequence<Is...>) {
    std::list<Base*> m;
    insertInMenu<0, typename std::tuple_element<Is, Tuple>::type...>(m);
    return m;
}

template <int N>
std::list<Base*> menu() {    
    using Tuple = typename obtainRange<Database, N>::type;
    return menu<N, Tuple>(std::make_index_sequence<std::tuple_size<Tuple>::value>{});
}

int main() {
    std::list<Base*> m = menu<0>();
    std::cout << "m.size() = " << m.size() << std::endl;  // 3
}
