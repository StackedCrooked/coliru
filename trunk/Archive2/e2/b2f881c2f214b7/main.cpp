#include <iostream>
#include <string>
#include <tuple>

template <typename T>
struct undefined;
void swallow(...) {}

void print_args() {
  std::cout << std::endl;
}
template <typename T, typename... Args>
void print_args(T&& arg1, Args&&... args) {
  std::cout << arg1 << "\t";
  print_args(std::forward<Args>(args)...);
}

/************index generator************/
template <size_t...>
struct indexes {};

template <size_t N, size_t... Indexes>
struct generate_indexes {
  typedef typename generate_indexes<N - 1, N - 1, Indexes...>::type type;
};

template <size_t... Indexes>
struct generate_indexes<0, Indexes...> {
  typedef indexes<Indexes...> type;
};
/*******endof index generator************/

template <typename T1, typename T2>
int print_pair(T1&& a1, T2&& a2) {
  print_args("!", std::forward<T1>(a1), std::forward<T2>(a2));
  return 0;
}

template <typename Tpl, size_t... Index>
void call_pair_impl(Tpl&& tpl, indexes<Index...>) {
  //swallow(print_args(Index, std::get<Index>(tpl))...); //gcc not want =(
  swallow(print_pair(Index, std::get<Index>(tpl))...);  
}

template <typename Tpl>
void call_pair(Tpl&& tpl) {
  typedef typename generate_indexes<std::tuple_size<
      typename std::remove_reference<Tpl>::type>::value>::type indexes_t;
  call_pair_impl(std::forward<Tpl>(tpl), indexes_t());
}
int main()
{
  call_pair(std::make_tuple(2.3, 13, "qwe", '?', std::string("i rly like variadics!")));
}