#include <iostream>
#include <functional>


namespace container
{
  template<char ...>
  struct string_t
  {
  };

  template<char Val>
  struct char_t
  {
    static const char value = Val;
  };

  template<int Val>
  struct int_t
  {
    static const int value = Val;
  };

  template <typename First, typename Second>
  struct pair
  {
    using first = First;
    using second = Second;
  };
}


namespace xutility
{
  template <typename T>
  struct get_head;

  template <char x, char ...xs>
  struct get_head<container::string_t<x, xs...>>
  {
    using type = container::string_t<x>;
  };


  template <typename T>
  struct get_tail;

  template <char x, char ...xs>
  struct get_tail<container::string_t<x, xs...>>
  {
    using type = container::string_t<xs...>;
  };


  template <typename Cont>
  using get_head_t = typename get_head<Cont>::type;

  template <typename Cont>
  using get_tail_t = typename get_tail<Cont>::type;
}


namespace io
{
  template <char ...text>
  std::ostream & operator << ( std::ostream & os, const container::string_t<text...> & )
  {
    for ( auto && i : { text... } )
      os << i << " ";
    return os;
  }

  std::ostream & operator << ( std::ostream & os, const container::string_t<> & )
  {
    return os << "empty";
  }

  template <int val>
  std::ostream & operator << ( std::ostream & os, const container::int_t<val> & )
  {
    return os << val << " ";
  }
}


namespace locale
{
  template <char ch>
  struct is_digit
  {
    static const bool value = ch >= '0' && ch <= '9';
  };

  template <char ch>
  struct is_alpha
  {
    static const bool value = ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
  };

}


namespace parser
{
  template<typename Str>
  struct str_to_int;

  template<char Ch>
  struct str_to_int<container::string_t<Ch>>
  {
    using type = container::int_t<Ch - '0'>;
  };

  template<char ...xs>
  struct str_to_int<container::string_t<xs...>>
  {
    using type = container::int_t<'0'>; //TODO полноценный парсер чисел
  };

  template<typename Str>
  using str_to_int_t = typename str_to_int<Str>::type;
}


namespace calculator
{
  template<typename Expr, typename Value>
  struct get_number;

  template<typename Expr, int Value>
  struct get_plus_minus;

  template<typename Expr, int Value>
  struct get_mul_div;


  template<typename Expr, typename Value = container::string_t<>>
  using get_number_t = typename get_number < Expr, Value >::type;


  template<char ...xs2>
  struct get_number<container::string_t<>, container::string_t<xs2...>>
  {
    using type = container::pair< parser::str_to_int_t< container::string_t<xs2...>>, container::string_t<> >;
  };

  template<char ...xs, char ...xs2>
  struct get_number<container::string_t<'(', xs...>, container::string_t<xs2...>>
  {
    using result = typename get_plus_minus<container::string_t<xs...>, 0>::type;

    using number_t = typename result::first;
    using rest_t = xutility::get_tail_t<typename result::second>;

    using type = container::pair< number_t, rest_t>;
  };

  template<char x, char ...xs, char ...xs2>
  struct get_number<container::string_t<x, xs...>, container::string_t<xs2...>>
  {
    using type =
      std::conditional_t
      <
      locale::is_digit< x >::value,
      get_number_t< container::string_t<xs...>, container::string_t<xs2..., x> >
      , container::pair< parser::str_to_int_t<container::string_t<xs2...>>, container::string_t<x, xs...> >
      >;
  };

  template< int val>
  struct get_mul_div <container::string_t<>, val>
  {
    using type = container::pair< container::int_t< val >, container::string_t<> >;
  };

  template<char ...xs, int val>
  struct get_mul_div <container::string_t<'*', xs...>, val>
  {
    using parse_result_t = get_number_t< container::string_t<xs...> >;
    using number_t = typename parse_result_t::first;
    using rest_t = typename parse_result_t::second;

    using type = typename get_mul_div< rest_t, val * number_t::value >::type;
  };

  template<char ...xs, int val>
  struct get_mul_div <container::string_t<'/', xs...>, val>
  {
    using parse_result_t = get_number_t< container::string_t<xs...> >;
    using number_t = typename parse_result_t::first;
    using rest_t = typename parse_result_t::second;

    using type = typename get_mul_div< rest_t, val / number_t::value >::type;
  };

  template<char ...xs, int val>
  struct get_mul_div <container::string_t<'+', xs...>, val>
  {
    using type = container::pair< container::int_t< val >, container::string_t<'+', xs...> >;
  };

  template<char ...xs, int val>
  struct get_mul_div <container::string_t<')', xs...>, val>
  {
    using type = container::pair< container::int_t< val >, container::string_t<')', xs...> >;
  };

  template<char ...xs, int val>
  struct get_mul_div <container::string_t<'-', xs...>, val>
  {
    using type = container::pair< container::int_t< val >, container::string_t<'-', xs...> >;
  };

  template<char x, char ...xs, int Value>
  struct get_mul_div <container::string_t<x, xs...>, Value>
  {
    using parse_result_t = get_number_t< container::string_t<x, xs...> >;
    using number_t = typename parse_result_t::first;
    using rest_t = typename parse_result_t::second;

    using type = typename get_mul_div< rest_t, number_t::value >::type;
  };




  template< int val>
  struct get_plus_minus <container::string_t<>, val>
  {
    using type = container::pair< container::int_t< val >, container::string_t<> >;
  };

  template<char ...xs, int val>
  struct get_plus_minus <container::string_t<'*', xs...>, val>
  {
    using type = container::pair< container::int_t< val >, container::string_t<'*', xs...> >;
  };

  template<char ...xs, int val>
  struct get_plus_minus <container::string_t<')', xs...>, val>
  {
    using type = container::pair< container::int_t< val >, container::string_t<')', xs...> >;
  };

  template<char ...xs, int val>
  struct get_plus_minus <container::string_t<'+', xs...>, val>
  {
    using parse_result_t = typename get_mul_div< container::string_t<xs...>, 0 >::type;
    using number_t = typename parse_result_t::first;
    using rest_t = typename parse_result_t::second;

    using type = typename get_plus_minus< rest_t, val + number_t::value >::type;
  };

  template<char ...xs, int val>
  struct get_plus_minus <container::string_t<'-', xs...>, val>
  {
    using parse_result_t = typename get_mul_div< container::string_t<xs...>, 0 >::type;
    using number_t = typename parse_result_t::first;
    using rest_t = typename parse_result_t::second;

    using type = typename get_plus_minus< rest_t, val - number_t::value >::type;
  };

  template<char x, char ...xs, int Value>
  struct get_plus_minus <container::string_t<x, xs...>, Value>
  {
    using parse_result_t = typename get_mul_div< container::string_t<x, xs...>, 0 >::type;
    using number_t = typename parse_result_t::first;
    using rest_t = typename parse_result_t::second;

    using type = typename get_plus_minus< rest_t, number_t::value >::type;
  };

}


namespace algorithm
{
}


int main()
{
  using namespace io;
  
  // Принимает только целые числа.
  // Числа от 0 до 9.
  // Деление тоже целочисленное.
  // Без унарных операций.
  
  using expr_1 = container::string_t<'2', '+', '2', '*', '2'>;
  std::cout << expr_1 {} << ": result " <<  calculator::get_plus_minus< expr_1, 0 >::type::first {} << std::endl;

  using expr_2 = container::string_t<'(', '2', '+', '2', ')', '*', '2'>;
  std::cout << expr_2 {} << ": result " <<  calculator::get_plus_minus< expr_2, 0 >::type::first {} << std::endl;

  // (5+9)*((7))*((9+(2)+(2+4)*2))/(5*9+5+3)
  using expr_3 = container::string_t<'(','5','+','9',')','*','(','(','7',')',')','*','(','(','9','+','(','2',')','+','(','2','+','4',')','*','2',')',')','/','(','5','*','9','+','5','+','3',')'>;
  std::cout << expr_3 {} << ": result " <<  calculator::get_plus_minus< expr_3, 0 >::type::first {} << std::endl;
//  std::cout << xutility::get_head_t<expr>{} << std::endl;
//  std::cout << xutility::get_tail_t<expr>{} << std::endl;

//  std::cout << calculator::get_number_t< expr >::first {} << std::endl;
//  std::cout << calculator::get_number_t< expr >::second {} << std::endl;

  //parser::str_to_int<container::string_t<'9'>>::value;
//  std::cout << parser::str_to_int_t<xutility::get_head_t<expr>>::value << std::endl;

//  std::cout << calculator::get_mul_div< expr, 0 >::number_t {} << std::endl;
//  std::cout << calculator::get_mul_div< expr, 0 >::rest_t {} << std::endl;
    
//  std::cout << calculator::get_mul_div< expr, 0 >::type::first {} << std::endl;
//  std::cout << calculator::get_mul_div< expr, 0 >::type::second {} << std::endl;


//  std::cout << calculator::get_plus_minus< expr, 0 >::number_t {} << std::endl;
//  std::cout << calculator::get_plus_minus< expr, 0 >::rest_t {} << std::endl;

//  std::cout << calculator::get_plus_minus< expr, 0 >::type::first {} << std::endl;
//  std::cout << calculator::get_plus_minus< expr, 0 >::type::second {} << std::endl;

  return EXIT_SUCCESS;
}
