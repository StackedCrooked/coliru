#include <iostream>
#include <list>

struct Base {};
struct A : Base {};  struct B : Base {};  struct C : Base {};
struct D : Base {};  struct E : Base {};  struct F : Base {};

template <int KEY, typename... RANGE> struct Map {};  // one-to-many map (mapping KEY to RANGE...)

template <typename...> struct Data {};

using Database = Data< Map<0, A,B,C>, Map<1, D,E>, Map<2, F> >;

template <int, typename>
struct find {};

template <int N, typename...Types, typename...Rest>
struct find<N, Data< Map<N, Types...>, Rest...>> {
    using type = Data<Types...>;
};

template <int N, typename T, typename...Rest>
struct find<N, Data< T, Rest...>> : 
    find<N, Data<Rest...>>::type {};

template <typename...Types>
std::list<Base*> menu(Data<Types...>) {
    return { new Types{}... };
}

template <int N>
std::list<Base*> menu() {
    return menu(typename find<N, Database>::type{});
}

int main() {
    std::list<Base*> m = menu<0>();
    std::cout << "m.size() = " << m.size() << std::endl;  // 3
}
