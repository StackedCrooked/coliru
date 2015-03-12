#include <type_traits>
#include <iostream>

template<class...>
struct voider { using type = void; };
template<class...Ts>
using void_t = typename voider<Ts...>::type;

template <class T, class U, class BinaryOperation, class Enable = void>
struct is_binop_able : std::false_type {};
template <class T, class U, class BinOp>
struct is_binop_able<T, U, BinOp, void_t<
  decltype(std::declval<BinOp>()(
    std::declval<T>(), std::declval<U>()))>> :
  std::true_type {};

#define RETURNS(...) \
  noexcept(noexcept(__VA_ARGS__)) \
    ->decltype(__VA_ARGS__) { \
      return (__VA_ARGS__); \
  }

struct plus {
  template <class T, class U>
  auto operator()(T t, U u) RETURNS(t + u)
};
template<class T, class U = T>
using is_addable = is_binop_able<T, U, plus>;

struct multiplies {
  template <class T, class U>
  auto operator()(T t, U u) RETURNS(t * u)
};
template<class T, class U = T>
using is_multiplicable = is_binop_able<T, U, multiplies>;

#undef RETURNS

int main()
{
  std::cout <<"is_addable\n";
  std::cout <<" long:   "<< is_addable<long>::type::value        <<'\n';
  std::cout <<" string: "<< is_addable<std::string>::type::value <<'\n';
  std::cout <<" void:   "<< is_addable<void>::type::value        <<'\n';
  std::cout <<" int*, int: "<< is_addable<int*, int>::type::value        <<'\n';

  std::cout <<"is_multiplicable\n";
  std::cout <<" long:   "<< is_multiplicable<long>::type::value        <<'\n';
  std::cout <<" string: "<< is_multiplicable<std::string>::type::value <<'\n';
  std::cout <<" void:   "<< is_multiplicable<void>::type::value        <<'\n';
}
