#include <type_traits>
#include <iostream>

template<class...>
struct voider { using type = void; };
template<class...Ts>
using void_t = typename voider<Ts...>::type;

template <class T, class BinaryOperation, class Enable = void>
struct is_binop_able_ : std::false_type {};
template <class T, class BinOp>
struct is_binop_able_<T, BinOp, void_t<
  decltype(std::declval<BinOp>()(
    std::declval<T>(), std::declval<T>()))>> :
  std::true_type {};
  
template <class T, class BinOp>
using is_binop_able = typename is_binop_able_<T,BinOp>::type;

template<class T>
using is_addable = is_binop_able<T, std::plus<T>>;

template<class T>
using is_multiplicable = is_binop_able<T, std::multiplies<T>>;

int main()
{
  std::cout <<"is_addable\n";
  std::cout <<" long:   "<< is_addable<long>::value        <<'\n';
  std::cout <<" string: "<< is_addable<std::string>::value <<'\n';
  std::cout <<" void:   "<< is_addable<void>::value        <<'\n';

  std::cout <<"is_multiplicable\n";
  std::cout <<" long:   "<< is_multiplicable<long>::value        <<'\n';
  std::cout <<" string: "<< is_multiplicable<std::string>::value <<'\n';
  std::cout <<" void:   "<< is_multiplicable<void>::value        <<'\n';
}
