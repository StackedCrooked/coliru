#include <iostream>

template <int... I> struct index_sequence {};
template <int N, int... I>
struct build_index_sequence : build_index_sequence<N-1,N-1,I...> {};
template <int... I>
struct build_index_sequence<0, I...> {
  using type = index_sequence<I...>;
};

template <int N>
using make_index_sequence = typename build_index_sequence<N>::type;

template <typename> struct square_of;

template <int... I>
struct square_of<index_sequence<I...>> {
  using type = index_sequence<(I*I)...>;
};

template <typename T>
using Square = typename square_of<T>::type;

template <typename> struct incr;

template <int... I>
struct incr<index_sequence<I...>> {
  using type = index_sequence<(I+1)...>;
};

template <typename T>
using Increment = typename incr<T>::type;

template <int... I>
void pow(index_sequence<I...>) {
    auto _{0, (std::cout << I << ' ', 0)...};
}

int main() {
    pow(Square<Increment<make_index_sequence<20>>>());
}
