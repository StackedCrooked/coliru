#include <type_traits>
#include <iostream>

template<class...>
struct voider { using type = void; };
template<class...Ts>
using void_t = typename voider<Ts...>::type;

template <class T, class U, class BinaryOperation, class Enable = void>
struct is_binop_able_ : std::false_type {};
template <class T, class U, class BinOp>
struct is_binop_able_<T, U, BinOp, void_t<
  decltype(std::declval<BinOp>()(
    std::declval<T>(), std::declval<U>()))>> :
  std::true_type {};
  
template <class T, class U, class BinOp>
using is_binop_able = typename is_binop_able_<T,U,BinOp>::type;

#define RETURNS(...) \
  noexcept(noexcept(__VA_ARGS__)) \
    ->decltype(__VA_ARGS__) { \
      return (__VA_ARGS__); \
  }

template<class T, class U = T>
using is_addable = is_binop_able<T, U, std::plus<>>;

template<class T, class U = T>
using is_multiplicable = is_binop_able<T, U, std::multiplies<>>;

#undef RETURNS

int main()
{
  std::cout <<"is_addable\n";
  std::cout <<" long:   "<< is_addable<long>::value        <<'\n';
  std::cout <<" string: "<< is_addable<std::string>::value <<'\n';
  std::cout <<" void:   "<< is_addable<void>::value        <<'\n';
  std::cout <<" int*, int: "<< is_addable<int*, int>::value        <<'\n';

  std::cout <<"is_multiplicable\n";
  std::cout <<" long:   "<< is_multiplicable<long>::value        <<'\n';
  std::cout <<" string: "<< is_multiplicable<std::string>::value <<'\n';
  std::cout <<" void:   "<< is_multiplicable<void>::value        <<'\n';
}
